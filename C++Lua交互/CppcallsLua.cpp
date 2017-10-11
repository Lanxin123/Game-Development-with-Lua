
#include "stdafx.h"
#include <iostream>  
#include <string.h>  
using namespace std;

extern "C"
{
#include "lua.h"  
#include "lauxlib.h"  
#include "lualib.h"  
}
void main()
{
	//1.����Lua״̬  
	lua_State *L = luaL_newstate();
	if (L == NULL)
	{
		return;
	}

	//2.����Lua�ļ�  
	int bRet = luaL_loadfile(L, "hello.lua");
	if (bRet)
	{
		cout << "load file error" << endl;
		return;
	}

	//3.����Lua�ļ�  
	bRet = lua_pcall(L, 0, 0, 0);
	if (bRet)
	{
		cout << "pcall error" << endl;
		return;
	}

	//4.��ȡ����  
	lua_getglobal(L, "str");
	string str = lua_tostring(L, -1);
	cout << "str = " << str.c_str() << endl;        //str = I am so cool~  

													//5.��ȡtable  
	lua_getglobal(L, "tbl");
	lua_getfield(L, -1, "name");
	str = lua_tostring(L, -1);
	cout << "tbl:name = " << str.c_str() << endl; //tbl:name = shun  

												  //6.��ȡ����  
	lua_getglobal(L, "add");        // ��ȡ������ѹ��ջ��  
	lua_pushnumber(L, 10);          // ѹ���һ������  
	lua_pushnumber(L, 20);          // ѹ��ڶ�������  
	int iRet = lua_pcall(L, 2, 1, 0);// ���ú�������������Ժ󣬻Ὣ����ֵѹ��ջ�У�2��ʾ����������1��ʾ���ؽ��������  
	if (iRet)                       // ���ó���  
	{
		const char *pErrorMsg = lua_tostring(L, -1);
		cout << pErrorMsg << endl;
		lua_close(L);
		return;
	}
	if (lua_isnumber(L, -1))        //ȡֵ���  
	{
		double fValue = lua_tonumber(L, -1);
		cout << "Result is " << fValue << endl;
	}

	//���ˣ�ջ�е�����ǣ�  
	//=================== ջ�� ===================   
	//  ����  ����      ֵ  
	//   4   int��      30   
	//   3   string��   shun   
	//   2   table:     tbl  
	//   1   string:    I am so cool~  
	//=================== ջ�� ===================   

	//7.�ر�state  
	lua_close(L);
	return;
}