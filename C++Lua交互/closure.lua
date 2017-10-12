-- 实现部分
function create_a_counter()
    local count=0
    return function()
        count = count + 1
        return count
    end
end

-- 调用部分
local mycounter = create_a_counter();

print("counter = "..mycounter())
print("counter = "..mycounter())
print("counter = "..mycounter())
print("counter = "..mycounter())
print("counter = "..mycounter())
print("counter = "..mycounter())
