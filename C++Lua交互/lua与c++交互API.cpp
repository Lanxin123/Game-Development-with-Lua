Lua5.1�ĳ���API
    lua_State
            Lua״̬�����Lua�������֧�ֶ��̣߳��ɴ������״̬��
    typedef int (*lua_Cfunction)(lua_State* L)
            Lua�����õ�C�����ĺ���ԭ�ͣ���C��������Ҫ�����ֺ������͵�
            ����ע�ᵽLua״̬���У��˺�Lua���ܵ��õ�C�ĺ���
            ����к���
            int c_Hello(lua_State* l)
            {
               luaL_checktype(l, 1, LUA_TSTRING)
               luaL_checktype(l, 2, LUA_TSTRING)    // �������������ַ���
                // ������ڶ����������������һ������
             printf("%s\t%s\n", lua_tostring(l,-1), lua_tostring(l, -2));
������������}
            ����C�����ʼ����ʱ��ִ�����´��룺
                    // ��������ѹ��LuaVMջ
                    lua_pushstring(l, "c_hello");
                    // ��������ַѹ��LuaVMջ
                    lua_pushcclosure(l, &c_Hello, 0)
                    // ��LuaVMջ�ϵ���������ȫ�ֱ���
                    lua_settable(l, LUA_GLOBALSINDEX)
            �˺���Lua�оͿ����������ã�
                    c_hello()
            ע��C������ʵ������в����Ļ����Ϊÿһ�������������ͼ��
                    ��ȷ����ջ��Ĳ����Ǻ�����������ƥ��
    lua_State* lua_newstate(lua_Alloc f, void* ud)
            �½�һ��LuaVM,����ֱ�ӵ���lua_open�������������
    void lua_close(lua_State* l))
            �ر�LuaVM
    ����ջ֡
            ��һ���������÷�����ʱ����γ���һ��ջ֡��������������ý���
            �����ջ֡����ʧ��
            ����Lua��������c_hello("Hello", "World")����ôc_Hello������
            ջ֡���Ǵ����Ĳ�����ʼ������ͼ��
            ����������������ʽ��ջ�����в����������͸�����    
			  ջ��ز���
            int (lua_gettop) (lua_State *L)
                    ȡ�õ�ǰʹ���˶���ջ�ռ�
            void (lua_settop) (lua_State *L, int idx)
                    ��ջ��������idx�����൱������һ�κ������øı���ջ֡
                    ������ʱ����� lua_settop(L, 1)�����Ѹ�ѹ��ջ����������ɾ��
            void (lua_pushvalue) (lua_State *L, int idx)
                    ���ջ֡�ĵ�idx��λ�õ�ֵѹ��ջ�����൱�ڸ���
            void (lua_remove) (lua_State *L, int idx)
                    ɾ����idx��λ�õ�ֵ
                    ���lua_remove(L, -2)��Ὣ"Hello"ɾ����ʣ��"World"��ջ��
                    ���ᱻ�Ƶ�ԭ��"Hello"��ŵ�λ��
            void (lua_insert) (lua_State *L, int idx);
                    �Ƚ��������ƻ����ƣ�����ջ����ֵѹ��ճ���λ��
            void (lua_replace) (lua_State *L, int idx)
                    ��ջ����ֵ�滻��idx����ֵ
            int (lua_checkstack) (lua_State *L, int sz)
                    ���ջ�Ĵ�С�Ƿ��Ѿ����������ֵ�����û����ջ�Ĵ�С����sz
                    ����0��ʾջ���������1��ʾ�ɹ�
            void (lua_xmove) (lua_State *from, lua_State *to, int n)
                    ��LavVM��ջ���ƶ�n��ֵ��to��LuaVM��ջ��
    ջ��ȡ����
            ���º�����ջ��ѹ��һ��Cֵ
            void (lua_pushnil) (lua_State *L)
                    ��ջ��ѹ��һ��NILֵ
            void (lua_pushnumber) (lua_State *L, lua_Number n)
                    ��ջ��ѹ��һ��ʵ��
            void (lua_pushinteger) (lua_State *L, lua_Integer n)
                    ��ջ��ѹ��һ������
            void (lua_pushlstring) (lua_State *L, const char *s, size_t l)
                    ��ջ��ѹ��һ�������ƴ�
            void (lua_pushstring) (lua_State *L, const char *s)
                    ��ջ��ѹ��һ���ַ���
            const char *(lua_pushvfstring) (lua_State *L, const char *fmt, va_list argp)
                    ��ջ��ѹ��һ����ʽ����������argp�Ǳ��
            const char *(lua_pushfstring) (lua_State *L, const char *fmt, ...)
                    ��ջ��ѹ��һ����ʽ����
            void (lua_pushcclosure) (lua_State *L, lua_CFunction fn, int n)
                    ѹ��һ������
            void (lua_pushboolean) (lua_State *L, int b)
                    ��ջ��ѹ��һ��bool����
            void (lua_pushlightuserdata) (lua_State *L, void *p)
                    ��ջ��ѹ��һ�����飬������ڴ��ָ��p
            int (lua_pushthread) (lua_State *L)
            ���º�������ջ�и���һ��ֵ����ջ��
            void (lua_gettable) (lua_State *L, int idx)
                    idxָ�����ջ�е�λ�ã�����ջ����keyȡ�ñ��е�ֵ��ѹ��ջ��
                    �˺�����lua_rawget���������ڴ˺��������metatable�ķ���
            void (lua_getfield) (lua_State *L, int idx, const char *k)
                    ��k����ջ�е�����(idx)��Ϊ������ȡ��k��Ӧ��ֵ��ѹ��ջ��
                    Ч����lua_gettable��ͬ
            void (lua_rawget) (lua_State *L, int idx)
                    idxָ�����ջ�е�λ�ã�����ջ����keyȡ�ñ��е�ֵ��ѹ��ջ��
                    Ϊ��������ݷ��ʵ�Ч�ʶ�ֱ�Ӷ�ȡ���е����ݣ�����Ҫ��metamethod�ĵ���
                    ���������ѭ����������Ԫ�رȽϷ���
            void (lua_rawgeti) (lua_State *L, int idx, int n)
                    idxָ�����ջ�е�λ�ã�nָ��key��ջ�е�λ�ã�ȡ�ñ��е�ֵ����ջ
                    �൱��:lua_pushnumber(L,n); lua_rawget(L,idx)
            void (lua_createtable) (lua_State *L, int narr, int nrec)
                    �½�һ����ѹ��ջ������Ĵ�СΪnarr����Ԥ����nrec��Ԫ�ؿռ�
            void *(lua_newuserdata) (lua_State *L, size_t sz)
                    ��ջ�з���һ���СΪsz���ڴ沢�ѹ���ṹ��ջ�ҷ����ڴ��ַ
            int (lua_getmetatable) (lua_State *L, int objindex)
                    objindexָ�������ջ�е�λ�ã�ȡ�ö����metatable������ѹ��ջ��
                    ���ʧ�ܻ��߶���û��metatable���򷵻�0
            void (lua_getfenv) (lua_State *L, int idx)
                    idxָ���������ջ�е�λ�ã�ȡ�ô˶��󲢽��价����ѹ��ջ
            ���º��������ж�ջ��ĳ��ֵ������
            int (lua_isnumber) (lua_State *L, int idx)
                    ջidx����ֵ�Ƿ���ʵ��
            int (lua_isstring) (lua_State *L, int idx)
                    ջidx����ֵ�Ƿ����ַ���
            int (lua_iscfunction) (lua_State *L, int idx)
                    ջidx����ֵ�Ƿ��Ǻ���
            int (lua_isuserdata) (lua_State *L, int idx)
                    ջidx����ֵ�Ƿ��Ƕ���������
            int (lua_type) (lua_State *L, int idx)
                    ȡ��ջidx����ֵ������
            const char *(lua_typename) (lua_State *L, int tp)
                    ������ת����C�ַ���
            int (lua_equal) (lua_State *L, int idx1, int idx2)
                    ջ������ֵ�Ƿ���ȣ����ͺ�ֵ����Ҫ��Ȳŷ�����
            int (lua_rawequal) (lua_State *L, int idx1, int idx2)
                    ջ�����������Ƿ���ȣ�����Ƕ���ʱ��ָ������ͬҲ�����
            int (lua_lessthan) (lua_State *L, int idx1, int idx2)
                    ջ������ֵ�Ĵ�С,idx1����ֵ�Ƿ�С��idx2����ֵ
            ���º�����ջ�ڵ�ĳ����ת����C������ֵ��ջ�ṹ����
            lua_Number (lua_tonumber) (lua_State *L, int idx)
                    ��idx��ָ���Luaֵת����ʵ������
            lua_Integer (lua_tointeger) (lua_State *L, int idx)
                    ��idx��ָ���Luaֵת������������
            int (lua_toboolean) (lua_State *L, int idx)
                    ��idx��ָ���Luaֵת����boolֵ����
            const char *(lua_tolstring) (lua_State *L, int idx, size_t *len)
                    ��idx��ָ���Luaֵת�����ַ������أ����ѳ��ȴ���len��
            size_t (lua_objlen) (lua_State *L, int idx)
                    ȡ��idx��ָ���Luaֵ����
            lua_Cfunction (lua_tocfunction) (lua_State *L, int idx)
                    ��idx��ָ���Luaֵת���ɺ�������
            void *(lua_touserdata) (lua_State *L, int idx)
                    ��idx��ָ���Luaֵת�����ڴ��(����)����
            lua_State *(lua_tothread) (lua_State *L, int idx)
                    ��idx��ָ���Luaֵת����LuaVM���󷵻�
            const void *(lua_topointer) (lua_State *L, int idx)
                    ȡ��idx��ָ�����ֵ�Ĵ洢��ַ����
            ���º��������Ӧ��get��������
            void (lua_settable) (lua_State *L, int idx)
            void (lua_setfield) (lua_State *L, int idx, const char *k)
            void (lua_rawset) (lua_State *L, int idx)
            void (lua_rawseti) (lua_State *L, int idx, int n)
            int (lua_setmetatable) (lua_State *L, int objindex)
            int (lua_setfenv) (lua_State *L, int idx)
    ��������
    �������ں�������
        ��������Ҫ����һ��Lua����ʱ����Ҫ������ѹ��ջ�У�Ȼ�����������ѹ��
            ����ͼ��


Lua��C/C++�Ľ��� - cp7618@yeah - cp7618@yeah�Ĳ���500)this.width=500;" border=0>
             ������Lua�������к���:
                function hello(x, y)
                 ��print(x, y)
                end
                ����C�п�������������:
              ��lua_getglobal(L, "hello"); -- ��ȫ������ȡ��hello������ѹ��ջ��
                lua_pushstring(L, "Hello");��-- ����ѹ����������
              ��lua_pushstring(L, "World");    
                lua_call(L, 2, 0); -- ������������ȡ�ú��������ô˺���,�����л�ȡ����Ӧ����
                                    
            void (lua_call) (lua_State *L, int nargs, int nresults)
                    �ޱ����ĺ�������
                    nargs��ָ���ú����Ĳ���������nresults��ָ�����õĺ����ķ���ֵ����
            int (lua_pcall) (lua_State *L, int nargs, int nresults, int errfunc)
                    ��lua_call���ƣ������˺������ڱ���ģʽ�±�����
                    �������������Ὣ����ѹ��ջ����������lua_callһ��
            int (lua_cpcall) (lua_State *L, lua_CFunction func, void *ud)
                    ֱ�ӵ���һ��C����������ud��Ϊfunc�������õĲ���
                    Ҳ����˵��func�����ڲ�������һ��������ud
            int (lua_load) (lua_State *L, lua_Reader reader, void *dt, const char *chunkname);

lua��c/c++�������ʵ������
         lua��ΪС�ɾ����Ľű����ԣ�����Ƕ��c/c++�� �� �㷺Ӧ������ϷAI ��ʵ�������κξ����仯���߼��϶�����ʹ��luaʵ�֣����c/c++ʵ�ֵĵײ�ӿڷ����ܹ���󽵵�ϵͳ��ά���ɱ��������lua��c/c++�Ľ���������һ��ʵ��������
lua�ṩ��API������c/c++�й���lua�����л�������ؽӿ����£�
//����lua����������
lua_State* luaL_newstate(void) ;
//����lua�ű��ļ�
int luaL_loadfile(lua_State *L, const char *filename);
lua��c/c++�����ݽ���ͨ��"ջ"���� ,��������ʱ�����Ƚ����ݿ�����"ջ"�ϣ�Ȼ���ȡ���ݣ�ջ�е�ÿ������ͨ������ֵ���ж�λ������ֵΪ��ʱ��ʾ�����ջ�׵�ƫ������������ֵΪ��ʱ��ʾ�����ջ����ƫ������������ֵ��1��-1Ϊ��ʼֵ�����ջ������ֵ��ԶΪ-1 ,ջ������ֵ��ԶΪ1 �� "ջ"�൱��������lua��c/c++֮�����ת�ء�ÿ�����ݶ�����Ӧ�Ĵ�ȡ�ӿ� ��
������"ջ"�ӿڣ�
void  (lua_pushnil) (lua_State *L);
void  (lua_pushnumber) (lua_State *L, lua_Number n);
void  (lua_pushinteger) (lua_State *L, lua_Integer n);
void  (lua_pushlstring) (lua_State *L, const char *s, size_t l);
void  (lua_pushstring) (lua_State *L, const char *s);
void  (lua_pushboolean) (lua_State *L, int b);
void  (lua_pushcclosure) (lua_State *L, lua_CFunction fn, int n);
���ݻ�ȡ�ӿڣ�
lua_Number      (lua_tonumber) (lua_State *L, int idx);
lua_Integer     (lua_tointeger) (lua_State *L, int idx);
int             (lua_toboolean) (lua_State *L, int idx);
const char     *(lua_tolstring) (lua_State *L, int idx, size_t *len);
lua_CFunction   (lua_tocfunction) (lua_State *L, int idx);
"ջ"�����ӿڣ�
int   (lua_gettop) (lua_State *L);
void  (lua_settop) (lua_State *L, int idx);
void  (lua_pushvalue) (lua_State *L, int idx);
void  (lua_remove) (lua_State *L, int idx);
void  (lua_insert) (lua_State *L, int idx);
void  (lua_replace) (lua_State *L, int idx);
int   (lua_checkstack) (lua_State *L, int sz);
lua�ж���ı����ͺ��������һ��ȫ��table�У�����ֵΪLUA_GLOBALSINDEX ��table��ز����ӿڣ�
void  (lua_gettable) (lua_State *L, int idx);
void  (lua_getfield) (lua_State *L, int idx, const char *k);
void  (lua_settable) (lua_State *L, int idx);
void  (lua_setfield) (lua_State *L, int idx, const char *k);
��"ջ"�а���ִ�нű���Ҫ������Ҫ��(�������Ͳ���)�󣬵���lua_pcallִ�нű���
int   (lua_pcall) (lua_State *L, int nargs, int nresults, int errfunc);
�������ʵ��˵����
func.lua
--��������
width=1 ;
height=2 ;
--lua�������壬ʵ�ּӷ�
function sum(a,b)
    return a+b ;
end
--lua�������壬ʵ���ַ������
function mystrcat(a,b)
    return a..b ;
end
--lua�������壬ͨ������c�����е�csum����ʵ�ּӷ�
function mysum(a,b)
    return csum(a,b) ;
end
test_lua.c
#include stdio.h>
#include stdlib.h>
#include string.h>
#include errno.h>
//luaͷ�ļ�
#include lua.h>
#include lualib.h>
#include lauxlib.h>
#define err_exit(num,fmt,args

)  \
    do{printf("[%s:%d]"fmt"\n",__FILE__,__LINE__,##args);exit(num);} while(0)
#define err_return(num,fmt,args

)  \
    do{printf("[%s:%d]"fmt"\n",__FILE__,__LINE__,##args);return(num);} while(0)
//lua�е��õ�c��������,ʵ�ּӷ�
int csum(lua_State* l)
{
    int a = lua_tointeger(l,1) ;
    int b = lua_tointeger(l,2) ;
    lua_pushinteger(l,a+b) ;
    return 1 ;
}
int main(int argc,char** argv)
{
    lua_State * l = luaL_newstate() ;        //����lua���л���
    if ( l == NULL ) err_return(-1,"luaL_newstat() failed"); 
    int ret = 0 ;
    ret = luaL_loadfile(l,"func.lua") ;      //����lua�ű��ļ�
    if ( ret != 0 ) err_return(-1,"luaL_loadfile failed") ;
    ret = lua_pcall(l,0,0,0) ;
    if ( ret != 0 ) err_return(-1,"lua_pcall failed:%s",lua_tostring(l,-1)) ;
    lua_getglobal(l,"width");              //��ȡlua�ж���ı���
    lua_getglobal(l,"height");
    printf("height:%ld width:%ld\n",lua_tointeger(l,-1),lua_tointeger(l,-2)) ;
    lua_pop(l,1) ;                        //�ָ�lua��ջ
    int a = 11 ;
    int b = 12 ;
    lua_getglobal(l,"sum");               //����lua�еĺ���sum
    lua_pushinteger(l,a) ;
    lua_pushinteger(l,b) ;
    ret = lua_pcall(l,2,1,0) ;
    if ( ret != 0 ) err_return(-1,"lua_pcall failed:%s",lua_tostring(l,-1)) ;
    printf("sum:%d + %d = %ld\n",a,b,lua_tointeger(l,-1)) ;
    lua_pop(l,1) ;
    const char str1[] = "hello" ;
    const char str2[] = "world" ;
    lua_getglobal(l,"mystrcat");          //����lua�еĺ���mystrcat
    lua_pushstring(l,str1) ;
    lua_pushstring(l,str2) ;
    ret = lua_pcall(l,2,1,0) ;
    if ( ret != 0 ) err_return(-1,"lua_pcall failed:%s",lua_tostring(l,-1)) ;
    printf("mystrcat:%s%s = %s\n",str1,str2,lua_tostring(l,-1)) ;
    lua_pop(l,1) ;
    lua_pushcfunction(l,csum) ;         //ע����lua��ʹ�õ�c����
    lua_setglobal(l,"csum") ;           //�󶨵�lua�е�����csum
    lua_getglobal(l,"mysum");           //����lua�е�mysum�������ú������ñ������ж����csum����ʵ�ּӷ�
    lua_pushinteger(l,a) ;
    lua_pushinteger(l,b) ;
    ret = lua_pcall(l,2,1,0) ;
    if ( ret != 0 ) err_return(-1,"lua_pcall failed:%s",lua_tostring(l,-1)) ;
    printf("mysum:%d + %d = %ld\n",a,b,lua_tointeger(l,-1)) ;
    lua_pop(l,1) ;
    lua_close(l) ;                     //�ͷ�lua���л���
    return 0 ;
}