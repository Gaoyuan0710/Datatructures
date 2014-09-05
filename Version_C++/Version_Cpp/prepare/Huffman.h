/*
 * =====================================================================================
 *
 *       Filename:  Huffman.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年11月15日 15时44分06秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  gaoyuan, 690892695@qq.com
 *        Company:  Class 1204 of Computer Science and Technology
 *
 * =====================================================================================
 */
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "Huffman_test.c"
#include "code.c"


#define MAX 256

Char_code *Count (char ch, Char_code *head);
void write_file(Char_code *head);
void show(Char_code *head);
void read_words(Char_code *head);
void trans_to_code(Char_code *head);
void read_file(Char_code *head);
void Print(HTNODE * ht, int num);
void Select (HTNODE * ht, int n,int *flag1, int *flag2);
void Creat_Huffman (HTNODE * ht, Char_code *head, int n);
void Get_Code (HTNODE * ht, char hc[][MAX], int n);
void write_import(HTNODE *ht, char ch[][MAX], int num, int flag);

