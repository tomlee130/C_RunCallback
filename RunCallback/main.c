//
//  main.c
//  RunCallback
//
//  Created by lory on 2024/5/30.
//

#include <stdio.h>
#include "run_callback_interface.h"
#include "run_read_file.h"

/// 读取文件
/// - Parameter filename: 文件名
const char * use_read_file(const char *filepath);

/// 主函数
/// - Parameters:
///   - argc: 参数个数
///   - argv: 参数值
int main(int argc, const char * argv[]);

void open_callback(int status) {
    switch (status) {
        case OPEN_CALLBACK_NOT_FOUND_ERROR:
            printf("not found filepath.\n");
            break;
        case OPEN_CALLBACK_OPEN_ERROR:
            printf("open file fail.\n");
            break;
        case OPEN_CALLBACK_MEMORY_ERROR:
            printf("memory alloc fail.\n");
        default:
            break;
    }
}

void open_callback_error(int status, const char * filepath) {
    switch (status) {
        case OPEN_CALLBACK_NOT_FOUND_ERROR:
            printf("not found filepath: %s\n", filepath);
            break;
        case OPEN_CALLBACK_OPEN_ERROR:
            printf("open file fail.\n");
            break;
        case OPEN_CALLBACK_MEMORY_ERROR:
            printf("memory alloc fail.\n");
        default:
            break;
    }
}

// 实现close_callback函数
void close_callback(int status) {
    if (status != CLOSE_CALLBACK_SUCCESS) {
        printf("callback closed error: %d.\n", status);
    }
}

/// 使用接口
/// - Parameter filepath: 文件路径
const char * use_read_file(const char *filepath) {
    
    void (^open_block_error)(int) = ^(int status) {
        switch (status) {
            case OPEN_CALLBACK_NOT_FOUND_ERROR:
                printf("not found filepath: %s\n", filepath);
                break;
            case OPEN_CALLBACK_OPEN_ERROR:
                printf("open file fail\n");
                break;
            case OPEN_CALLBACK_MEMORY_ERROR:
                printf("memory alloc fail\n");
            default:
                break;
        }
    };
    
    void (^close_block)(int) = ^(int status) {
        if (status != CLOSE_CALLBACK_SUCCESS) {
            printf("callback closed error: %d.\n", status);
        }
    };
    
    run_block_interface block_interface = {
        .open_block_error = open_block_error,
        .close_block = close_block
    };
    
    return read_file_block(filepath, block_interface);
}

int main(int argc, const char * argv[]) {
    const char * filepath = "";
    if (argc >= 2) {
        filepath = argv[1];
    } else {
        printf("help: ./RunCallback example.txt\n");
        return 0;
    }
    
    const char * content = use_read_file(filepath);
    
    if (content != NULL) {
        printf("%s\n", content);
    }
    
    run_block_interface block_interface = {
        .open_block_error = ^(int status) {
            open_callback_error(status, filepath);
        },
        .close_block = ^(int status) {
            close_callback(status);
        }
    };
    
    content = read_file_block(filepath, block_interface);
    
    if (content != NULL) {
        printf("%s\n", content);
    }
    
    run_callback_interface callback_interface = {
        .open_callback_error = open_callback,
        .close_callback = close_callback
    };
    
    content = read_file(filepath, &callback_interface);
    
    if (content != NULL) {
        printf("%s\n", content);
    }
    
    return 0;
}
