Lua可以定义不定长的参数列表。使用（...）代替参数列表，Lua会创建一个局部的名字为org的table，
保存所有调用时传递的参数，以及参数个数（通过arg.n获取）。      
function HowMany(...)   --或（val1，val2 ，...）
    if arg.n > 0 then
        for indx = 1,arg.n do
        local myString = string.format("%s%d","Argument",indx,":")
        print(myString,arg[indx])
    end
 else
    print("No variables entered.")
 end
end

assert(myValue){}
assert函数可以让你像处理函数一样运行编译后的Lua代码块（chunk）。
也可以用loadstring函数直接执行代码块，但他不能像assert函数一共报错功能。
myString = "math.max(7,8,9,10)"
loadstring(myString)()

dofile(filename)
通常我们用它来载入定义函数的文件以备调用，除此之外还可以用来载入数据文件。

math.floor()
floor函数用来向下取整(Lua中没有浮点数或者整数的概念)，该函数只是舍去小数部分。
如果想四舍五入取整一个数字，那么可以先给它加上0.5，然后再向下取整。
a = 5.125
b = 5.75
a = 5+0.5
b = b + 0.5
a = math.floor(a) -- a will equal 5
b = math.floor(b) -- b will equal 6

math.random()
在游戏开发过程中，随机函数随处可见。math.random()函数随机生成一个0~1之间的伪随机数。
myDie = math.random(1,6)

math.min()
math.min函数返回最小值，math.max函数返回最大值。
function GetMin(theTable)
	myString = "myValue = math.min ("
	for index,value in ipairs(theTable) do
		myString = string.format("%s%d%s",myString,value,",")
	end

	myString = string.sub(myString,1,string.len(myString)-1)
	myString = string.format("%s%s",myString,")")
	loadstring(myString)()
	return myValue
end

类型转换
字符和数字之间的转换可以用tonumber()函数
myString="1234"
myNumber = tonumber(myString)
print(myNumber + 2)
print(type(myNumber))
还可以使用tostring()函数把数字转换成字符
myNumber = 1234
myString = tostring(myNumber)
print(type(myString))

字符处理

string.char(n1,n2,...)
string。char函数根据ASCII编码返回传入参数对应的字符。这个函数不是很常用，但在Lua游戏保存文件中插入一个换行符的时候
非常有用，便于阅读。
myFile:write(string.char(10))--write out a linefeed to the open
file

string.len(myString)
该函数可以返回传入参数的字符数。
myString = "1234"
print(string.len(myString))

string.sub(myString,start,end)
string.sub函数返回指定字符串的子串。start参数指定子串的开始位置，end指定子串的结束位置。
myString = "hello world"
newString = string.sub(myString,1,5)--输出区间内的字符
print(newString)


myString = "hello world"
newString =  string.sub(myString,-5,10)--输出从倒数五个字符到第十个字符
print(newString)

--end参数可以省略，这时函数会返回从start到字符串末尾的字符串。通过这种方式可以获取指定字符的后缀
myString = "hello world.cpp"
newString = string.sub(myString,-3)
print(newString)

string.format()
string.format函数可以让你格式化输出指定字符串。在输出字符串到GUI界面时，这个函数很常用。我们可以用这个函数来
连接字符串(Lua不能简单地链接到两个字符串)

string1 = "hello"
string2 = "world"
for index = 1,3 do
	string1 = string.format("%s%s",string1,string2)
end
print(string1)--prints "helloworldworldworld"

string.format的另一个主要用途是根据参数格式化输出复杂的字符串。
myName = "Fred"
myStr = 16
myString = string.format("%s%s%d%s",myName,"s strength is ",myStr,".")
print(myString)

string.find(sourceString,findString)
string.find该函数会在sourceString中查找第一个符合findString字符的位置。如果找到了该目标字符
则返回它的开始和结束位置；如果没有找到则返回nil
myString = "My name is John Smith."
sStart,sEnd = string.find(myString,'John')
print(sStart,sEnd)--prints "12 15"


myString = "The price is $17.50."
filter = "$%d%d.%d%d"
print(string.sub(myString,string.find(myString,filter)))--filter参数指定了我们需要查找内容的格式
--使用大写字符可以得到相反的格式，如%d表示所有数字，%D则表示非数字。


string.gsub(sourceString,pattern,replacementString)
--sourceString 字符中满足pattern格式的字符都会被替换成replacementString参数的值。
myString = "My name is John Smith. My phone is 555-3257."
newString = string.gsub(myString,"%d","*")
print(newString)

--可在函数的最后加一个可选参数，用于指定替换的次数
myString = "happy,hello,home,hot,hudson"
myString = string.gsub(myString,"h%a+","An H word!",2)
print(myString)


string.gfind函数遍历一个字符串，一旦查找到符合指定格式的字符串就返回该子串
myString = "This is my rather 1 long string."
print(myString)
counter = 1
for myWord in string.gfind(myString,"%a+")do
	print(string.format("Worc #%d: %s",counter,myWord))
	counter = counter + 1
end

table的数据结构
myTable = {}
for index = 1,100 do
	myTable[index] = math.random(1,1000)
end

table.getn()返回table中元素的个数。
print(table.getn(myTable))

for index = 1,table.getn(myTable) do
	print(myTable[index])
end

sort遍历了整个table，并从小到大重新排列。还可以添加函数名作为另一个参数，
然后通过该函数得到比较的结果来排序。
table.sort(myTable)

function Sort(theTable,direction)
	if direction ~= 1 then
		table.sort(theTable)
	else
		function Reverse(a,b)
			if a<b then
				return false
			else
				return true
			end
		end
		table.sort(theTable,Reverse)
	end
end

table.insert(myTable,position,value)
table.insert函数在table中插入一个新的值，位置参数是可选的 ，如果没设定，会添加新的值到table末尾，
如果指定了该值，则插入到指定的位置。

table.insert(myTable,25,"hello")

tabl.remove函数从指定table中删除并返回一个元素，必要时重新索引table。
--如果没有指定position的值，则默认删除table的最后一个元素
print(table.remove(myTable,25))

table不仅能使用其他的值作为索引值。
myData = {}
myData.name = "Thardwick"
myData.class = "Barbarian"
myData.str = math.random(3,18)
myData.dex = math.random(3,18)

myData[1] = 17
myData[2] = 34
myData[3] = 24

多维table
widget = {}
widget.name = {}
widget.cost = {}
widget.name[1] = "Can opener"
widget.cost[1] = "$12.75"
widget.name[2] = "Scissors"
widget.cost[2] = "$8.99"

pairs()函数可以遍历table中的每一个元素。

myNames = {"Fred","Enthel","Lucy","Ricky","Rockey","Betsy","Bill"}
for index,value in pairs(myNames) do
	print(index,value)
end


a = {1,2,3}
for index,value in pairs(a) do--index是table的序号，value
	print(index,value)
end

myData = {}
myData.name = "Billy"
myData.interest = "Wind surfing"
myData.quote = "Cold out,eh?"
myData.shoesize = 11
for index,value in pairs(myData) do
	print(index,value)
end

o.open函数有两个参数：文件名和输出方式。w代表写模式，如果文件不存在则创建一个文件，
同时写入时会覆盖之前的数据。作为游戏进度的保存，我们一般会使用这种方式。
myFile = io.open("HelloWorld.lua",'w')
if myFile ~= nil then
	myFile:write("--Test lua file")
	myFile:write(string.char(10))
	myFile:write(string.char(10))
	myFile:write(string.format("%s%s","--File created on: ",
	os.date()))--系统时间
	myFile:write(string.char(10))
	myFile:write(string.char(10))
	myFile:write("print(\"hello world!\")")
	io.close(myFile)
end














