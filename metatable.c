
// lua元表
/*
    元表
    如果一个tableB调用setmetatable方法设置另外一个tableA作为它的元表，那么你操作tableB进行如：设置键值、查找键值、
    table间使用运算符号、或者直接传个参数调用等操作时就会变得不一样或者原本不可行操作的现在可行了。而tableA之所以能
    成为元表，是因为里面包含了特殊的键代表着特殊的含义，代码在运行时会做特殊的处理，下面会一一做介绍。

    首先记住两个函数：
        setmetatable(table, metatable)
        对指定table设置元表(metatable)，如果元表(metatable)中存在__metatable键值，setmetatable会失败。

        getmetatable(table)
        返回对象的元表(metatable)。如元表中存在__metatable键值，返回元表会失败。

        __metatable键值是用于安全考虑，可以防止获取和修改表中的内容。

        下面实例演示如何设置元表：
            metatable = {} -- 元表
            
            table = {} -- 普通表

            setmetatable(table, metatable) -- 将metatable设置为table的元表

        也可以直接这么写：

            setmetatable({}, {})

        返回元表：

            getmetatable(table) -- 返回metatable

    1.访问和设值：
        当你通过一个键访问table的时候，如果这个table中没有这个键值对，但它设置了元表，且元表中有__index这个键，如果
        __index是一个表，那么程序就会到一个表中去查找，如果__index的值为一个函数，那么程序就会调用这个函数：

            local tableA = {k2 = "Hello"}

            local tableB = {k1 = "Hi"}

            setmetatable(tableB, {__index = tableA})

            print(tableB.k2)

            打印：

            Hello

        __index值为函数：

            function fn(table, key)

                print(table, "\n", key)

                return "Hello"

            end

            local tableB = {k1 = "Hi"}

            setmetatable(tableB, {__index = fn}) -- 会将table和key作为参数传给fn

            print(tableB.k2)

            打印：

            table：000000000067a690

            k2

            Hello

        __newindex键
            __index用于访问，__newindex用于设置新值。当一个table设置了元表，为这个table设置键值的时候，如果这个键存在，
            那么直接修改当前键值；如果这个键不存在，那么会操作元表中__newindex相应的值。__newindex值为一个table或者函数。

                local tableA = {}

                local tableB = setmetatable({k1 = "Hi"}, {__newindex = tableA})

                tableB.k1 = "HiHi"

                tableB.k2 = "Hello"

                print(tableB.k1, tableB.k2, tableA.k2)

                打印结果：
                
                HiHi nil Hello     -- tableA被设置了新值

            __newindex的值为函数：

                function fn(table, key, value)
                
                    print(table, "\n", key, "\n", value)

                end

                local tableB = {k1 = "Hi"}

                setmetable(tableB, {__newindex = fn})  -- 会将table、key、value传给fn作为参数

                tableB.k2 = "Good"

                打印结果：

                table: 000000000256a650

                k2

                Good

    2.运算符
        当我们想table与table之间使用"+、-、*、/、==、<="运算符时，就的通过元表来实现。
*/