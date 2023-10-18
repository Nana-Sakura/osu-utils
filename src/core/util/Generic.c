#include "utils/core/util/Generic.h"

void write_file(const char* path_to_file,const char* file_content,const char* write_mode){
    FILE* fp=fopen(path_to_file,write_mode);
    fprintf(fp,"%s",file_content);
    fclose(fp);
}
 
char* read_file(const char* path){
    FILE* fp=fopen(path,"r");
    size_t file_size=get_file_size(path);
    char* string=calloc((file_size+1),sizeof(char));
    fgets(string,(file_size+1),fp);
    fclose(fp);
    return string;
}

size_t get_file_size(const char* path){
    struct stat stat_buf;
    int rc=stat(path,&stat_buf);
    return (rc==0)?stat_buf.st_size:-1;
}

time_t get_last_modified_time(const char* path){
    struct stat stat_buf;
    int rc=stat(path,&stat_buf);
    return (rc==0)?stat_buf.st_mtimespec.tv_sec:-1;
}

int check_expire(const char* path){
    time_t current_time=time(NULL);
    int time_delta=current_time-get_last_modified_time(path);
    return (time_delta<86400)?0:-1;
}

char* strfsec(int length){
    if((length>=86400)||(length<=0)){
        LOG("The beatmap is not aimed for humans.");
        exit(16);
    }
    int hrs=length/3600;
    length%=3600;
    int min=length/60;
    length%=60;
    int vaild_num=3;
    if(hrs==0){
        vaild_num--;
    }
    char* result=malloc(vaild_num*3*sizeof(char));
    if(vaild_num==3){
        sprintf(result,"%d:%02d:%02d",hrs,min,length);
    }
    else{
        sprintf(result,"%d:%02d",min,length);
    }
    return result;
}

char* strf_mod_intro(cJSON* mods){
    int mod_count=cJSON_GetArraySize(mods);
    char* mods_string=malloc((3*mod_count+3)*sizeof(char));
    strcpy(mods_string," ");
    if(mod_count>0){
        strcat(mods_string,"+");
        for(int j=0;j<mod_count;j++){
            cJSON* mod=cJSON_GetArrayItem(mods,j);
            strcat(mods_string,mod->valuestring);
            strcat(mods_string," ");
        }
    }
    return mods_string;
}

void show_progress(int task_now,int task_sum,int width){
    float progress=(float)task_now/(float)task_sum;
    int end_position=width*progress;
    printf("[");
    for(int i=0;i<width;i++){
        if(i<end_position){
            printf("=");
        }
        else if(i==end_position){
            printf(">");
        }
        else{
            printf(" ");
        }
    }
    printf("] %.1f%%\r",progress*(float)100);
    fflush(stdout);
}

int search_array(const char** array,int len,const char* val){
    for(int i=0;i<len;i++){
        if(strcmp(array[i],val)==0){
            return i;
        }
    }
    exit(-1);
}
