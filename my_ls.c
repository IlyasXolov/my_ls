#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
typedef struct listnode {
    struct listnode* next;
    char* name;
    struct stat fs;
}listnode; 

void my_print_to_all(listnode* node_file_ , char flag){
    while(node_file_ != NULL){
        if(flag == 't' || !flag){
            if(node_file_->name[0] != '.') {
            printf("%s\n", node_file_->name);
            }
        }
        else{
            printf("%s\n", node_file_->name);
        }
        node_file_ = node_file_->next;
    }
}

int my_cmp_node_str(char*  param1, char*  param2){
    int k =0;
    for(; param1[k] == param2[k] && param1[k] != '\0' && param2[k] != '\0';k++){
        }
    return param1[k] - param2[k];
}
listnode* my_add_last_my_unversal(listnode *nodes, char * name,struct stat filestat){
    listnode* temp1 = malloc(sizeof(listnode));
    temp1->name = name;
    temp1->next = NULL;
    temp1->fs = filestat;
    if(nodes == NULL){
        nodes = temp1;
    }
    else{
        listnode* temp2 = nodes;
        while (temp2->next != NULL){
            temp2 = temp2->next;
        }
        temp2->next = temp1;
    }
    return nodes;
}
void my_swap(listnode*  head, listnode* N_next){
char* swap = (char*)malloc(50);
    struct stat filestat;
    swap = head->name;
    head->name =N_next->name;
    N_next->name = swap;
    filestat = head->fs;
    head->fs = N_next->fs;
    N_next->fs = filestat;
} 
       
listnode* my_sort_function_to_all(listnode* node_file,char flag){
    listnode* head_file = node_file;
    while(head_file->next != NULL){
        listnode* headers_next = head_file->next;
        while(headers_next != NULL){
            if(flag == 't'|| flag == 'z'){
                if( head_file->fs.st_mtim.tv_sec == headers_next->fs.st_mtim.tv_sec ){
                    if( head_file->fs.st_mtim.tv_nsec <= headers_next->fs.st_mtim.tv_nsec ){
                        char* swap=(char*)malloc(50);
                        struct stat filestat;
                        swap=head_file->name;
                        head_file->name=headers_next->name;
                        headers_next->name=swap;
                        filestat=head_file->fs;
                        head_file->fs=headers_next->fs;
                        headers_next->fs=filestat;
                    }
                }
                else if( head_file->fs.st_mtim.tv_sec <= headers_next->fs.st_mtim.tv_sec )
                {
                char* swap = (char*)malloc(50);
                struct stat filestat;
                swap=head_file->name;
                head_file->name=headers_next->name;
                headers_next->name=swap;
                filestat=head_file->fs;
                head_file->fs=headers_next->fs;
                headers_next->fs=filestat;
                }
            }
            else{
                if(my_cmp_node_str(head_file->name, headers_next->name)>= 0){
                    my_swap(head_file, headers_next);
                }
                }
                headers_next = headers_next->next;
        }
        head_file = head_file->next;
    }
    return node_file;
}
void my_open_func_in_ls(char flag){
    DIR *directory;
    directory = opendir(".");
    struct dirent *entry;
    struct stat fil_s;
    listnode* node_file = (listnode*)malloc(sizeof(listnode) );
    node_file=NULL;
        while((entry= readdir(directory))) {
            stat(entry->d_name, &fil_s);
            node_file = my_add_last_my_unversal(node_file, entry->d_name, fil_s);
        }
    node_file = my_sort_function_to_all(node_file, flag);
    my_print_to_all(node_file, flag);
    closedir(directory);
} 

listnode* my_personal(){\
    listnode* temp1 =(listnode*)malloc(sizeof(listnode));
    listnode* temp2 =(listnode*)malloc(sizeof(listnode));
    listnode* temp3 =(listnode*)malloc(sizeof(listnode));
        temp1->name = ".";
        temp2->name = "/";
        temp3->name = "/tmp/";
            temp1->next = temp2;
            temp2->next = temp3;
            temp3->next = NULL;
    return temp1;
}
void my_func_file_or_dir_identifier( listnode* list_node , char flag ){
    struct stat ft;
    listnode* files_N = (listnode*)malloc(sizeof(listnode)); files_N = NULL ;
    listnode* files_D = (listnode*)malloc(sizeof(listnode)); files_D = NULL;
    int fd,file_len = 0,dir_len = 0;
    while(list_node){
        fd = open(list_node->name, O_RDONLY);
        if(fd >= 0){
            stat(list_node->name,&ft);
            if(!S_ISDIR(ft.st_mode)){
                files_N  =  my_add_last_my_unversal(files_N, list_node->name, ft);
                file_len++;
            }else{
                files_D = my_add_last_my_unversal(files_D, list_node->name, ft);
                if(my_cmp_node_str(list_node->name, "/") == 0){
                    files_D = my_personal();
                }
                dir_len++ ;
            }
        }
        else
        {
        printf("ls: cannot access '%s': No such file or directory\n", list_node->name);
        }
        list_node = list_node->next;
    }
    if(file_len > 0){
        files_N = my_sort_function_to_all(files_N,  flag);
        while(files_N){
            files_N = files_N->next;
        }
    }
    if(dir_len > 0){
        DIR* directory;
        struct dirent *entry;
        struct stat ft;
        while(files_D){
            listnode* place_node =(listnode*)malloc(sizeof(listnode));
            place_node = NULL;
            directory = opendir(files_D->name);
            while((entry = readdir(directory))){
                stat(entry->d_name, &ft);
                place_node = my_add_last_my_unversal(place_node , entry->d_name , ft);
            }
            place_node = my_sort_function_to_all(place_node, flag);
            if( dir_len >1){
                printf("%s:\n", files_D->name);
            }
            my_print_to_all(place_node, flag);
            if(files_D->next != NULL){
                putchar('\n'); 
            }
            files_D = files_D->next;
        }
    }
}
 void flages(){
    int i = 0;
    while(i<10){
        i++;
    }
}           
 void my_ls(int argc_size,char** argv_array){
                struct stat fs;
                listnode *place_node = malloc(sizeof(listnode));
                place_node = NULL;
                int  a = 0, t = 0, at=0;
                int length = 0;
                for(int i = 1; i < argc_size; i++){
                    if(my_cmp_node_str(argv_array[i], "-a")== 0)
                     a = 1;
                    else if(my_cmp_node_str(argv_array[i] , "-t")== 0)
                     t = 1;
                    else if(my_cmp_node_str(argv_array[i], "-at")==0 || my_cmp_node_str(argv_array[i], "-ta")==0)
                     at=1;
                    else{
                        length++;
                        stat(argv_array[i], &fs);
                        place_node = my_add_last_my_unversal(place_node, argv_array[i], fs);
                    }
                }
            char flag;
                if(t==1 && a==1){
                    flag = 'z';
                }
                else if(at==1){
                    flag='z';
                }
                else if(t==1){
                flag = 't';
                }
                else if(a==1){
                flag = 'a';
                }
                if(length == 0){
                my_open_func_in_ls(flag);
                }
                else{
                    my_func_file_or_dir_identifier(place_node, flag);
                }
            }
int main(int argc,char** argv){
    my_ls(argc,argv);
}
            

