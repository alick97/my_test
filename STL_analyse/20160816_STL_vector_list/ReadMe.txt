1 增加 MyAllocator.h ---------- 空间适配器
      将MyVectory和 MyList的空间获取、释放方式由new、delete转为由控件适配器分配和释放
      提高效率
2 增加 Typetraits.h  ---------- 类型萃取
      将平凡类型（如int）和需要构造的类型（如string）区分开，这样用去其他需要拷贝的函数，
       将类型区分开处理，效率更高
3 增加 Construct.h  ----------- 实现通用的构造和析构
        里面用到类型萃取，效率更高
4 增加 Uninitialized.h ---------  拷贝一段初始化、未初始化的数据的通用函数
        用到类型萃取、特化


基本上实现了 
      STL中List、Vector、空间适配器的简单模拟