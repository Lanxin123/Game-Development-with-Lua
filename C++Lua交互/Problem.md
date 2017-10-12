//转自：http://cn.cocos2d-x.org/tutorial/show?id=1474
Lua和C++交互

Lua和C/C++语言通信的主要方法使一个无处不在的虚拟栈。栈的特点是先进后出。
在Lua中，Lua地毡就是一个struct，堆栈索引的方式可以是正数也可以是负数，
区别是：正数索引1永远表示栈底，负数索引永远表示栈顶。


TValue stack[max_stack_len]  // 欲知内情可以查 lstate.c 的stack_init函数
存入栈的数据类型包括数值, 字符串, 指针, talbe, 闭包等。


lua的栈是在创建lua_State的时候创建的:
lua_pushcclosure(L, func, 0) // 创建并压入一个闭包

lua_createtable(L, 0, 0)        // 新建并压入一个表

lua_pushnumber(L, 343)      // 压入一个数字

lua_pushstring(L, “mystr”)   // 压入一个字符串

这里要说明的是, 你压入的类型有数值, 字符串, 表和闭包
[在c++中看来是不同类型的值], 但是最后都是统一用TValue这种数据结构来保存的)如图Lua_1所示







TValue结构对应于lua中的所有数据类型, 是一个{值, 类型} 结构, 这就lua中动态类型的实现, 它把值和类型绑在一起, 
用tt记录value的类型, value是一个联合结构, 由Value定义, 可以看到这个联合有四个域, 先说明简单的

p -- 可以存一个指针, 实际上是lua中的light userdata结构

n -- 所有的数值存在这里, 不过是int , 还是float

b -- Boolean值存在这里, 注意, lua_pushinteger不是存在这里, 而是存在n中, b只存布尔

gc -- 其他诸如table, thread, closure, string需要内存管理垃圾回收的类型都存在这里

gc是一个指针, 它可以指向的类型由联合体GCObject定义, 从图中可以看出, 有string, userdata, closure, table, proto, upvalue, thread
 
从下面的图可以的得出如下结论:

1. lua中, number, boolean, nil, light userdata四种类型的值是直接存在栈上元素里的, 和垃圾回收无关.

2. lua中, string, table, closure, userdata, thread存在栈上元素里的只是指针, 他们都会在生命周期结束后被垃圾回收.

堆栈的操作

因为Lua与C/C++是通过栈来通信，Lua提供了C API对栈进行操作。

我们先来看一个最简单的例子：
Stack operation.cpp

其他一些栈操作：
int   lua_gettop (lua_State *L);            //返回栈顶索引（即栈长度）  
void  lua_settop (lua_State *L, int idx);   //                
void  lua_pushvalue (lua_State *L, int idx);//将idx索引上的值的副本压入栈顶  
void  lua_remove (lua_State *L, int idx);   //移除idx索引上的值  
void  lua_insert (lua_State *L, int idx);   //弹出栈顶元素，并插入索引idx位置  
void  lua_replace (lua_State *L, int idx);  //弹出栈顶元素，并替换索引idx位置的值

C++调用Lua
我们经常可以使用Lua文件来作配置文件。类似ini，xml等文件配置信息。现在我们来使用C++来读取Lua文件中的变量，table，函数。

lua和c通信时有这样的约定: 所有的lua中的值由lua来管理, c++中产生的值lua不知道, 类似表达了这样一种意思: "如果你(c/c++)想要什么, 你告诉我(lua), 我来产生, 然后放到栈上, 你只能通过api来操作这个值, 我只管我的世界", 这个很重要, 因为:

"如果你想要什么, 你告诉我, 我来产生"就可以保证, 凡是lua中的变量, lua要负责这些变量的生命周期和垃圾回收, 所以, 必须由lua来创建这些值(在创建时就加入了生命周期管理要用到的簿记信息)

"然后放到栈上, 你只能通过api来操作这个值", lua api给c提供了一套完备的操作界面, 这个就相当于约定的通信协议, 如果lua客户使用这个操作界面, 那么lua本身不会出现任何"意料之外"的错误.

"我只管我的世界"这句话体现了lua和c/c++作为两个不同系统的分界, c/c++中的值, lua是不知道的, lua只负责它的世界。


现有Hello.lua文件以及Stack operation


知道怎么读取后，我们来看下如何修改上面代码中table的值：

// 将需要设置的值设置到栈中  
lua_pushstring(L, "我是一个大帅锅～");  
// 将这个值设置到table中（此时tbl在栈的位置为2）  
lua_setfield(L, 2, "name");
我们还可以新建一个table：

// 创建一个新的table，并压入栈  
lua_newtable(L);  
// 往table中设置值  
lua_pushstring(L, "Give me a girl friend !"); //将值压入栈  
lua_setfield(L, -2, "str"); //将值设置到table中，并将Give me a girl friend 出栈


需要注意的是：堆栈操作是基于栈顶的，就是说它只会去操作栈顶的值。

举个比较简单的例子，函数调用流程是先将函数入栈，参数入栈，然后用lua_pcall调用函数，此时栈顶为参数，栈底为函数，所以栈过程大致会是：参数出栈->保存参数->函数出栈->调用函数->返回结果入栈。

类似的还有lua_setfield，设置一个表的值，肯定要先将值出栈，保存，再去找表的位置。

另外补充一下：

lua_getglobal(L,"var")会执行两步操作：1.将var放入栈中，2.由Lua去寻找变量var的值，并将变量var的值返回栈顶（替换var）。

lua_getfield(L,-1,"name")的作用等价于 lua_pushstring(L,"name") + lua_gettable(L,-2)//？？？？？？？？？
// void (lua_gettable) (lua_State *L, int idx)
//idx指向表在栈中的位置，弹出栈顶的key取得表中的值并压入栈顶
 


**********************************************？？？？？？？？？？？？？？？？？？？？
lua value 和 c value的对应关系

 	           c	         lua
         nil	          无	   {value=0, tt = t_nil}
      boolean	      int  非0, 0	   {value=非0/0， tt = t_boolean}
      number	      int/float等   1.5	   {value=1.5, tt = t_number}
   lightuserdata	   void*, int*, 各种*  point	   {value=point, tt = t_lightuserdata}
      string	         char  str[]	   {value=gco, tt = t_string}   gco=TString obj
      table	           无	   {value=gco, tt = t_table}  gco=Table obj
      userdata	           无	   {value=gco, tt = t_udata} gco=Udata obj
      closure	           无	   {value=gco, tt = t_function} gco=Closure obj
***********************************************？？？？？？？？？？？？？？？？？？？？ 

可以看出来, lua中提供的一些类型和c中是对应的, 也提供一些c中没有的类型. 其中有一些药特别的说明一下:

nil值, c中没有对应, 但是可以通过lua_pushnil向lua中压入一个nil值

注意: lua_push*族函数都有"创建一个类型的值并压入"的语义, 因为lua中所有的变量都是lua中创建并保存的, 对于那些和c中有对应关系的lua类型, lua会通过api传来的附加参数, 
创建出对应类型的lua变量放在栈顶, 对于c中没有对应类型的lua类型, lua直接创建出对应变量放在栈顶.

例如:    lua_pushstring(L, “string”) lua根据"string"创建一个 TString obj, 绑定到新分配的栈顶元素上

         lua_pushcclosure(L,func, 0) lua根据func创建一个 Closure obj, 绑定到新分配的栈顶元素上

         lua_pushnumber(L,5) lua直接修改新分配的栈顶元素, 将5赋值到对应的域

         lua_createtable(L,0, 0)lua创建一个Tabke obj, 绑定到新分配的栈顶元素上
总之, 这是一个 c value –> lua value的流向, 不管是想把一个简单的5放入lua的世界, 还是创建一个table, 都会导致

1. 栈顶新分配元素    2. 绑定或赋值

还是为了重复一句话, 一个c value入栈就是进入了lua的世界, lua会生成一个对应的结构并管理起来, 从此就不再依赖这个c value

lua value –> c value时, 是通过 lua_to* 族api实现, 很简单, 取出对应的c中的域的值就行了, 只能转化那些c中有对应值的lua value, 比如table就不能to c value, 所以api中夜没有提供 lua_totable这样的接口.










