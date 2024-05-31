//
//  run_callback_module.h
//  RunCallback
//
//  Created by lory on 2024/5/30.
//

#ifndef run_callback_module_h
#define run_callback_module_h

#define ACCESS_FILE_SUCCESS 0
#define ACCESS_FILE_NOT_FOUND_ERROR (-1)
//#define ACCESS_FILE_NOT_READ_ERROR (-2)
//#define ACCESS_FILE_NOT_WRITE_ERROR (-3)

//#define OPEN_CALLBACK_SUCCESS 0
#define OPEN_CALLBACK_NOT_FOUND_ERROR (-1)
#define OPEN_CALLBACK_OPEN_ERROR (-2)
#define OPEN_CALLBACK_MEMORY_ERROR (-3)

#define CLOSE_CALLBACK_SUCCESS 0

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

#endif /* run_callback_module_h */
