# C_RunCallback
```C
// 定义一个结构体，其中包含函数指针
typedef struct {
    void (*open_callback_error)(int);
    void (*close_callback)(int);
} run_callback_interface;

// 定义一个结构体，其中包含函数闭包
typedef struct {
    void (^open_block_error)(int);
    void (^close_block)(int);
} run_block_interface;
```
