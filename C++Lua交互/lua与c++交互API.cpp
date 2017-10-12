Lua5.1的常用API
    lua_State
            Lua状态机或叫Lua虚拟机，支持多线程，可创建多个状态机
    typedef int (*lua_Cfunction)(lua_State* L)
            Lua所调用的C函数的函数原型，在C程序中需要将这种函数类型的
            函数注册到Lua状态机中，此后Lua才能调用到C的函数
            如果有函数
            int c_Hello(lua_State* l)
            {
               luaL_checktype(l, 1, LUA_TSTRING)
               luaL_checktype(l, 2, LUA_TSTRING)    // 两个参数都是字符串
                // 先输出第二个参数，后输出第一个参数
             printf("%s\t%s\n", lua_tostring(l,-1), lua_tostring(l, -2));
　　　　　　}
            需在C程序初始化的时候执行以下代码：
                    // 将函数名压入LuaVM栈
                    lua_pushstring(l, "c_hello");
                    // 将函数地址压入LuaVM栈
                    lua_pushcclosure(l, &c_Hello, 0)
                    // 把LuaVM栈上的这个表放入全局表中
                    lua_settable(l, LUA_GLOBALSINDEX)
            此后在Lua中就可以这样调用：
                    c_hello()
            注：C函数的实现如果有参数的话最好为每一个参数进行类型检查
                    以确保所栈里的参数是函数参数类型匹配
    lua_State* lua_newstate(lua_Alloc f, void* ud)
            新建一个LuaVM,可以直接调用lua_open来调用这个函数
    void lua_close(lua_State* l))
            关闭LuaVM
    关于栈帧
            当一个函数调用发生的时候就形成了一个栈帧，当这个函数调用结束
            后这个栈帧就消失了
            如在Lua这样调用c_hello("Hello", "World")，那么c_Hello所看到
            栈帧就是从它的参数开始，如下图：
            可以有两种索引方式对栈顶进行操作，正数和负数。    
			  栈相关操作
            int (lua_gettop) (lua_State *L)
                    取得当前使用了多少栈空间
            void (lua_settop) (lua_State *L, int idx)
                    把栈顶设置在idx处，相当于做了一次函数调用改变了栈帧
                    如果这个时候调用 lua_settop(L, 1)，则会把刚压入栈的两个参数删除
            void (lua_pushvalue) (lua_State *L, int idx)
                    向此栈帧的第idx个位置的值压入栈顶，相当于复制
            void (lua_remove) (lua_State *L, int idx)
                    删除第idx个位置的值
                    如果lua_remove(L, -2)则会将"Hello"删除而剩下"World"在栈顶
                    并会被移到原来"Hello"存放的位置
            void (lua_insert) (lua_State *L, int idx);
                    先将整个上移或下移，并将栈顶的值压入空出的位置
            void (lua_replace) (lua_State *L, int idx)
                    把栈顶的值替换掉idx处的值
            int (lua_checkstack) (lua_State *L, int sz)
                    检查栈的大小是否已经增长到最大值，如果没有则将栈的大小增长sz
                    返回0表示栈溢出，返回1表示成功
            void (lua_xmove) (lua_State *from, lua_State *to, int n)
                    从LavVM的栈顶移动n个值到to的LuaVM的栈顶
    栈存取操作
            以下函数往栈顶压入一个C值
            void (lua_pushnil) (lua_State *L)
                    往栈顶压入一个NIL值
            void (lua_pushnumber) (lua_State *L, lua_Number n)
                    往栈顶压入一个实数
            void (lua_pushinteger) (lua_State *L, lua_Integer n)
                    往栈顶压入一个整数
            void (lua_pushlstring) (lua_State *L, const char *s, size_t l)
                    往栈顶压入一个二进制串
            void (lua_pushstring) (lua_State *L, const char *s)
                    往栈顶压入一个字符串
            const char *(lua_pushvfstring) (lua_State *L, const char *fmt, va_list argp)
                    往栈顶压入一个格式化串，不过argp是变参
            const char *(lua_pushfstring) (lua_State *L, const char *fmt, ...)
                    往栈顶压入一个格式化串
            void (lua_pushcclosure) (lua_State *L, lua_CFunction fn, int n)
                    压入一个函数
            void (lua_pushboolean) (lua_State *L, int b)
                    往栈顶压入一个bool类型
            void (lua_pushlightuserdata) (lua_State *L, void *p)
                    往栈顶压入一个数组，数组的内存块指向p
            int (lua_pushthread) (lua_State *L)
            以下函数往从栈中复制一个值存入栈顶
            void (lua_gettable) (lua_State *L, int idx)
                    idx指向表在栈中的位置，弹出栈顶的key取得表中的值并压入栈顶
                    此函数与lua_rawget的区别在于此函数会调用metatable的方法
            void (lua_getfield) (lua_State *L, int idx, const char *k)
                    以k所在栈中的索引(idx)作为参数，取得k对应的值并压入栈顶
                    效率与lua_gettable相同
            void (lua_rawget) (lua_State *L, int idx)
                    idx指向表在栈中的位置，弹出栈顶的key取得表中的值并压入栈顶
                    为了提高数据访问的效率而直接读取表中的数据，不需要对metamethod的调用
                    这个函数在循环访问数组元素比较方便
            void (lua_rawgeti) (lua_State *L, int idx, int n)
                    idx指向表在栈中的位置，n指向key在栈中的位置，取得表中的值并入栈
                    相当于:lua_pushnumber(L,n); lua_rawget(L,idx)
            void (lua_createtable) (lua_State *L, int narr, int nrec)
                    新建一个表并压入栈顶，表的大小为narr，并预留了nrec个元素空间
            void *(lua_newuserdata) (lua_State *L, size_t sz)
                    在栈中分配一块大小为sz的内存并把管理结构入栈且返回内存地址
            int (lua_getmetatable) (lua_State *L, int objindex)
                    objindex指向对象在栈中的位置，取得对象的metatable并将其压入栈顶
                    如果失败或者对象没有metatable表则返回0
            void (lua_getfenv) (lua_State *L, int idx)
                    idx指向对象所在栈中的位置，取得此对象并将其环境量压入栈
            以下函数用于判断栈内某处值的类型
            int (lua_isnumber) (lua_State *L, int idx)
                    栈idx处的值是否是实数
            int (lua_isstring) (lua_State *L, int idx)
                    栈idx处的值是否是字符串
            int (lua_iscfunction) (lua_State *L, int idx)
                    栈idx处的值是否是函数
            int (lua_isuserdata) (lua_State *L, int idx)
                    栈idx处的值是否是二进制数据
            int (lua_type) (lua_State *L, int idx)
                    取得栈idx处的值的类型
            const char *(lua_typename) (lua_State *L, int tp)
                    将类型转换成C字符串
            int (lua_equal) (lua_State *L, int idx1, int idx2)
                    栈内两个值是否相等，类型和值都需要相等才返回真
            int (lua_rawequal) (lua_State *L, int idx1, int idx2)
                    栈内两个对象是否相等，如果是对象时所指对象相同也算相等
            int (lua_lessthan) (lua_State *L, int idx1, int idx2)
                    栈内两个值的大小,idx1处的值是否小于idx2处的值
            以下函数将栈内的某个格转换成C能理解的值，栈结构不变
            lua_Number (lua_tonumber) (lua_State *L, int idx)
                    将idx所指向的Lua值转换成实数返回
            lua_Integer (lua_tointeger) (lua_State *L, int idx)
                    将idx所指向的Lua值转换成整数返回
            int (lua_toboolean) (lua_State *L, int idx)
                    将idx所指向的Lua值转换成bool值返回
            const char *(lua_tolstring) (lua_State *L, int idx, size_t *len)
                    将idx所指向的Lua值转换成字符串返回，并把长度存入len中
            size_t (lua_objlen) (lua_State *L, int idx)
                    取得idx所指向的Lua值长度
            lua_Cfunction (lua_tocfunction) (lua_State *L, int idx)
                    将idx所指向的Lua值转换成函数返回
            void *(lua_touserdata) (lua_State *L, int idx)
                    将idx所指向的Lua值转换成内存块(数组)返回
            lua_State *(lua_tothread) (lua_State *L, int idx)
                    将idx所指向的Lua值转换成LuaVM对象返回
            const void *(lua_topointer) (lua_State *L, int idx)
                    取得idx所指对象的值的存储地址返回
            以下函数与其对应的get函数类似
            void (lua_settable) (lua_State *L, int idx)
            void (lua_setfield) (lua_State *L, int idx, const char *k)
            void (lua_rawset) (lua_State *L, int idx)
            void (lua_rawseti) (lua_State *L, int idx, int n)
            int (lua_setmetatable) (lua_State *L, int objindex)
            int (lua_setfenv) (lua_State *L, int idx)
    函数调用
    　　关于函数调用
        　　当需要调用一个Lua函数时，先要将函数压入栈中，然后将其参数依次压入
            如下图：


Lua与C/C++的交互 - cp7618@yeah - cp7618@yeah的博客500)this.width=500;" border=0>
             假设在Lua代码中有函数:
                function hello(x, y)
                 　print(x, y)
                end
                则在C中可以这样来调用:
              　lua_getglobal(L, "hello"); -- 从全局域中取得hello函数并压入栈顶
                lua_pushstring(L, "Hello");　-- 依次压入两个参数
              　lua_pushstring(L, "World");    
                lua_call(L, 2, 0); -- 跳过两个参数取得函数并调用此函数,函数中会取得相应参数
                                    
            void (lua_call) (lua_State *L, int nargs, int nresults)
                    无保护的函数调用
                    nargs是指调用函数的参数个数，nresults是指所调用的函数的返回值个数
            int (lua_pcall) (lua_State *L, int nargs, int nresults, int errfunc)
                    与lua_call相似，不过此函数是在保护模式下被调用
                    如果发生错误则会将错误压入栈，否则功能与lua_call一样
            int (lua_cpcall) (lua_State *L, lua_CFunction func, void *ud)
                    直接调用一个C函数，并把ud做为func函数调用的参数
                    也就是说在func函数内部看来第一个参数是ud
            int (lua_load) (lua_State *L, lua_Reader reader, void *dt, const char *chunkname);

lua和c/c++互相调用实例分析
         lua作为小巧精悍的脚本语言，易于嵌入c/c++中 ， 广泛应用于游戏AI ，实际上在任何经常变化的逻辑上都可以使用lua实现，配合c/c++实现的底层接口服务，能够大大降低系统的维护成本。下面对lua和c/c++的交互调用做一个实例分析：
lua提供了API用于在c/c++中构造lua的运行环境，相关接口如下：
//创建lua运行上下文
lua_State* luaL_newstate(void) ;
//加载lua脚本文件
int luaL_loadfile(lua_State *L, const char *filename);
lua和c/c++的数据交互通过"栈"进行 ,操作数据时，首先将数据拷贝到"栈"上，然后获取数据，栈中的每个数据通过索引值进行定位，索引值为正时表示相对于栈底的偏移索引，索引值为负时表示相对于栈顶的偏移索引，索引值以1或-1为起始值，因此栈顶索引值永远为-1 ,栈底索引值永远为1 。 "栈"相当于数据在lua和c/c++之间的中转地。每种数据都有相应的存取接口 。
数据入"栈"接口：
void  (lua_pushnil) (lua_State *L);
void  (lua_pushnumber) (lua_State *L, lua_Number n);
void  (lua_pushinteger) (lua_State *L, lua_Integer n);
void  (lua_pushlstring) (lua_State *L, const char *s, size_t l);
void  (lua_pushstring) (lua_State *L, const char *s);
void  (lua_pushboolean) (lua_State *L, int b);
void  (lua_pushcclosure) (lua_State *L, lua_CFunction fn, int n);
数据获取接口：
lua_Number      (lua_tonumber) (lua_State *L, int idx);
lua_Integer     (lua_tointeger) (lua_State *L, int idx);
int             (lua_toboolean) (lua_State *L, int idx);
const char     *(lua_tolstring) (lua_State *L, int idx, size_t *len);
lua_CFunction   (lua_tocfunction) (lua_State *L, int idx);
"栈"操作接口：
int   (lua_gettop) (lua_State *L);
void  (lua_settop) (lua_State *L, int idx);
void  (lua_pushvalue) (lua_State *L, int idx);
void  (lua_remove) (lua_State *L, int idx);
void  (lua_insert) (lua_State *L, int idx);
void  (lua_replace) (lua_State *L, int idx);
int   (lua_checkstack) (lua_State *L, int sz);
lua中定义的变量和函数存放在一个全局table中，索引值为LUA_GLOBALSINDEX ，table相关操作接口：
void  (lua_gettable) (lua_State *L, int idx);
void  (lua_getfield) (lua_State *L, int idx, const char *k);
void  (lua_settable) (lua_State *L, int idx);
void  (lua_setfield) (lua_State *L, int idx, const char *k);
当"栈"中包含执行脚本需要的所有要素(函数名和参数)后，调用lua_pcall执行脚本：
int   (lua_pcall) (lua_State *L, int nargs, int nresults, int errfunc);
下面进行实例说明：
func.lua
--变量定义
width=1 ;
height=2 ;
--lua函数定义，实现加法
function sum(a,b)
    return a+b ;
end
--lua函数定义，实现字符串相加
function mystrcat(a,b)
    return a..b ;
end
--lua函数定义，通过调用c代码中的csum函数实现加法
function mysum(a,b)
    return csum(a,b) ;
end
test_lua.c
#include stdio.h>
#include stdlib.h>
#include string.h>
#include errno.h>
//lua头文件
#include lua.h>
#include lualib.h>
#include lauxlib.h>
#define err_exit(num,fmt,args

)  \
    do{printf("[%s:%d]"fmt"\n",__FILE__,__LINE__,##args);exit(num);} while(0)
#define err_return(num,fmt,args

)  \
    do{printf("[%s:%d]"fmt"\n",__FILE__,__LINE__,##args);return(num);} while(0)
//lua中调用的c函数定义,实现加法
int csum(lua_State* l)
{
    int a = lua_tointeger(l,1) ;
    int b = lua_tointeger(l,2) ;
    lua_pushinteger(l,a+b) ;
    return 1 ;
}
int main(int argc,char** argv)
{
    lua_State * l = luaL_newstate() ;        //创建lua运行环境
    if ( l == NULL ) err_return(-1,"luaL_newstat() failed"); 
    int ret = 0 ;
    ret = luaL_loadfile(l,"func.lua") ;      //加载lua脚本文件
    if ( ret != 0 ) err_return(-1,"luaL_loadfile failed") ;
    ret = lua_pcall(l,0,0,0) ;
    if ( ret != 0 ) err_return(-1,"lua_pcall failed:%s",lua_tostring(l,-1)) ;
    lua_getglobal(l,"width");              //获取lua中定义的变量
    lua_getglobal(l,"height");
    printf("height:%ld width:%ld\n",lua_tointeger(l,-1),lua_tointeger(l,-2)) ;
    lua_pop(l,1) ;                        //恢复lua的栈
    int a = 11 ;
    int b = 12 ;
    lua_getglobal(l,"sum");               //调用lua中的函数sum
    lua_pushinteger(l,a) ;
    lua_pushinteger(l,b) ;
    ret = lua_pcall(l,2,1,0) ;
    if ( ret != 0 ) err_return(-1,"lua_pcall failed:%s",lua_tostring(l,-1)) ;
    printf("sum:%d + %d = %ld\n",a,b,lua_tointeger(l,-1)) ;
    lua_pop(l,1) ;
    const char str1[] = "hello" ;
    const char str2[] = "world" ;
    lua_getglobal(l,"mystrcat");          //调用lua中的函数mystrcat
    lua_pushstring(l,str1) ;
    lua_pushstring(l,str2) ;
    ret = lua_pcall(l,2,1,0) ;
    if ( ret != 0 ) err_return(-1,"lua_pcall failed:%s",lua_tostring(l,-1)) ;
    printf("mystrcat:%s%s = %s\n",str1,str2,lua_tostring(l,-1)) ;
    lua_pop(l,1) ;
    lua_pushcfunction(l,csum) ;         //注册在lua中使用的c函数
    lua_setglobal(l,"csum") ;           //绑定到lua中的名字csum
    lua_getglobal(l,"mysum");           //调用lua中的mysum函数，该函数调用本程序中定义的csum函数实现加法
    lua_pushinteger(l,a) ;
    lua_pushinteger(l,b) ;
    ret = lua_pcall(l,2,1,0) ;
    if ( ret != 0 ) err_return(-1,"lua_pcall failed:%s",lua_tostring(l,-1)) ;
    printf("mysum:%d + %d = %ld\n",a,b,lua_tointeger(l,-1)) ;
    lua_pop(l,1) ;
    lua_close(l) ;                     //释放lua运行环境
    return 0 ;
}