# 定义数组
array = ['alice\\n', 'bob\\n', 'cat\\n']

for person in array:
    print(person)
    
for person in array:
    person = person.strip('\\n')
    print(person)