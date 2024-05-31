//
//  run_read_file.h
//  RunCallback
//
//  Created by lory on 2024/5/30.
//

#ifndef run_read_file_h
#define run_read_file_h

#include "run_callback_interface.h"

/// 文件是否存在
/// - Parameter filepath: 文件路径
int access_file(const char *filepath);

/// 读取文件
/// - Parameters:
///   - filepath: 文件路径
///   - callback: 闭包回调的结构体指针
void read_file(const char *filepath, run_callback_interface *callback);

/// 读取文件
/// - Parameters:
///   - filepath: 文件路径
///   - callback: 闭包回调的结构体指针
void read_file_block(const char *filepath, run_block_interface callback);


#endif /* run_read_file_h */
