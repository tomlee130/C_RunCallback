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


# C callback base interface

```C
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
```
# impl biz
```C
char *read_file_block(const char *filepath, run_block_interface callback) {
    int status;
    if (0 != access_file(filepath)) {
        callback.open_block_error(OPEN_CALLBACK_NOT_FOUND_ERROR);
        return NULL;
    }
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        callback.open_block_error(OPEN_CALLBACK_OPEN_ERROR);
        return NULL;
    }
 
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);
    
    char *content = (char*)malloc((size_t) (size + 1));
    if (content == NULL) {
        callback.open_block_error(OPEN_CALLBACK_MEMORY_ERROR);
        if ((status = fclose(file)) != 0) {
            callback.close_block(status);
        }
        return NULL;
    }
 
    fread(content, 1, (size_t) size, file);
    content[size] = '\0';
 
    if (0 != (status = fclose(file))) {
        callback.close_block(status);
    }
    return content;
}
```
