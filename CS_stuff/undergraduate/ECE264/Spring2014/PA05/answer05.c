#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "answer05.h"

Image * Image_load(const char * filename){
  FILE *fp = fopen(filename, "rb");
  int err = 0;
  if(fp == NULL) err = 1;
  Image *tmpin = NULL;
  Image *img = NULL;
  if(err) fprintf(stderr, "Cannot open '%s'!", filename);
  
  ImageHeader head;
  size_t read;
  if(!err){
    read = fread(&head, sizeof(ImageHeader), 1, fp);
    if(read != 1 || head.magic_number != ECE264_IMAGE_MAGIC_NUMBER ||
       head.width == 0 || head.height == 0 || head.comment_len ==0)
      err = 1;
  }
  if(err) fprintf(stderr, "header crash.\n");
  if(!err){
    tmpin = malloc(sizeof(Image));
    if(tmpin == NULL) err = 1;
    if(err) fprintf(stderr, "Error when allocating memory.\n");
  }
  if(!err){
    tmpin -> width = head.width;
    tmpin -> height = head.height;
    tmpin -> comment = malloc(sizeof(char) * head.comment_len);
    tmpin -> data = malloc(sizeof(char) * (head.width * head.height));
    if(tmpin->comment==NULL || tmpin->data==NULL) err = 1;
    if(err) fprintf(stderr,"Error when allocating memory to data and comment.\n" );
  }
  if(!err){
    read = fread(tmpin->comment, sizeof(char), head.comment_len, fp);
    if(read!=head.comment_len || tmpin->comment[head.comment_len-1]!='\0') err = 1;
    if(err) fprintf(stderr, "Cannot read the comment.\n");
  }
  if(!err){
    read = fread(tmpin->data, sizeof(char), head.width*head.height, fp);
    if(read!=(head.width*head.height)) err = 1;
    if(err) fprintf(stderr, "Cannot read data.\n");
  }
  if(!err){
    fgetc(fp);
    if(!feof(fp)) err = 1;
    if(err) fprintf(stderr, "File reading did not complete.\n");
  }
  if(!err){
    img = tmpin;
    tmpin = NULL;
    return img;
  }
  if(tmpin!=NULL){
    free(tmpin->comment);
    free(tmpin->data);
    free(tmpin);
  }
  if(fp != NULL) fclose(fp);
  
  return NULL;
}


void linearNormalization(int width, int height, uint8_t * intensity){
  int max = intensity[0];
  int min = intensity[0];
  int i, j;
  for(i = 0; i < width*height; i++){
    if(intensity[i] < min)
      min = intensity[i];
    if(intensity[i] > max)
      max = intensity[i];
  }
  for(j = 0; j < width*height; j++){
    intensity[j] = (intensity[j] - min) * 255 / (max - min);
  }
  
}

void Image_free(Image * image){
  free(image->comment);
  free(image->data);
  free(image);
}

int Image_save(const char * filename, Image * image){
  int err = 0;
  FILE *fp = NULL;
  //uint8_t * buffer = NULL;
  ImageHeader head;
  size_t written = 0;
  fp = fopen(filename, "w");
  if(fp == NULL){
    err = 1;
    fprintf(stderr, "Cannot open '%s' for writing.\n", filename);
    return 0;
  }
  if(!err){
    head.magic_number = ECE264_IMAGE_MAGIC_NUMBER;
    head.width = image->width;
    head.height = image->height;
    head.comment_len = strlen(image->comment) + 1;
    
    written = fwrite(&head, sizeof(ImageHeader), 1, fp);
    written = fwrite(image->comment, sizeof(char), head.comment_len, fp);
    written = fwrite(image->data, sizeof(uint8_t), (head.width*head.height), fp);
  }
  return written;
}

  

