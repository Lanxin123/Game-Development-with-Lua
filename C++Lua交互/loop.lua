--����һ��table
local Languages =
{
	"lua",
	"c",
	"c++",
	"java",
	"python",
}
local elementnum = table.getn(Languages);

-- while ѭ��
print("\nwhile loop result:")

local index = 1;
while index <= elementnum do
	print("["..index.."] = "..Languages[index]);
	index = index + 1;
end

--repeat ѭ��
print("\nrepeat loop result:")

local index = 1;
repeat
	print("["..index.."] = ".. Languages[index]);
    index = index + 1;
until index > elementnum

--for ѭ��
print("\nfor loop result:")

for index = 1,elementnum do
	print("["..index.."] = ".. Languages[index]);
end

--generic for ѭ��
print("\ngeneric for loop result:")

for index,value in pairs(Languages) do
	print("["..index.."] = "..value)
end






