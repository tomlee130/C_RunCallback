//
//  run_read_file.c
//  RunCallback
//
//  Created by lory on 2024/5/30.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "run_read_file.h"

int access_file(const char *filepath) {
    if (ACCESS_FILE_SUCCESS != access(filepath, F_OK)) {
        return ACCESS_FILE_NOT_FOUND_ERROR;
    }
    
    return 0;
}

void read_file_block(const char *filepath, run_block_interface callback) {
    int status;
    if (0 != access_file(filepath)) {
        callback.open_block_error(OPEN_CALLBACK_NOT_FOUND_ERROR);
        return;
    }
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        callback.open_block_error(OPEN_CALLBACK_OPEN_ERROR);
        return;
    }
 
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);
    
    char *content = (char*)malloc((size_t) (size + 1));
    if (content == NULL) {
        callback.open_block_error(OPEN_CALLBACK_MEMORY_ERROR);
        if ((status = fclose(file)) != 0) {
            callback.close_block(status, NULL, NULL);
        }
        return;
    }
 
    fread(content, 1, (size_t) size, file);
    content[size] = '\0';
 
    status = fclose(file);
    callback.close_block(status, content, ^(void){
        free((void *)content);  // 外部回到给外部，用完再释放内存
    });
}

void demalloc_mem_block(const char * content) {
    free((void *)content);
}

void read_file(const char *filepath, run_callback_interface *callback) {
    // 创建一个接口实例
    run_block_interface block_interface = {
        .open_block_error = ^(int status) {
            callback->open_callback_error(status);
        },
        .close_block = ^(int status, const char *content, demalloc_mem func) {
            callback->close_callback(status, content, ^(void){
                func();
            });
        }
    };
    
    read_file_block(filepath, block_interface);
}
