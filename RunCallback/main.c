//
//  main.c
//  RunCallback
//
//  Created by lory on 2024/5/30.
//

#include <stdio.h>
#include "run_callback_interface.h"
#include "run_read_file.h"
#include <stdlib.h>
#include <string.h>

/// 读取文件
/// - Parameter filename: 文件名
void use_read_file(const char *filepath);

/// 主函数
/// - Parameters:
///   - argc: 参数个数
///   - argv: 参数值
int main(int argc, const char * argv[]);

/// 使用接口
/// - Parameter filepath: 文件路径
void use_read_file(const char *filepath) {
    
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
    
    void (^close_block)(int, const char *, demalloc_mem) = ^(int status, const char * content, demalloc_mem callback_func) {
        if (status != CLOSE_CALLBACK_SUCCESS) {
            printf("callback closed error: %d.\n", status);
        }
        
        if (content != NULL) {
            printf("%s\n", content);
        }
        // TODO: 处理完成业务逻辑,最后释放
        callback_func();
    };
    
    run_block_interface block_interface = {
        .open_block_error = open_block_error,
        .close_block = close_block
    };
    read_file_block(filepath, block_interface);
}

int main(int argc, const char * argv[]) {
    const char * filepath = "";
    if (argc >= 2) {
        filepath = argv[1];
    } else {
        printf("help: ./RunCallback example.txt\n");
        return 0;
    }
    
    use_read_file(filepath);

    return 0;
}
