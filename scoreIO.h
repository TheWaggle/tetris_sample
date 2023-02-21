#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

struct Buffer {
    char *data;
    int data_size;
};

size_t buffer_writer(char *ptr, size_t size, size_t nmemb, void *stream) {
    struct Buffer *buf = (struct Buffer *)stream;
    int block = size * nmemb;
    if (!buf) {
        return block;
    }

    if (!buf->data) {
        buf->data = (char *)malloc(block+1);
    }
    else {
        buf->data = (char *)realloc(buf->data, buf->data_size + block+1);
    }

    if (buf->data) {
        memcpy(buf->data + buf->data_size, ptr, block);
        buf->data_size += block;
    }

    return block;
}

int post_score(char *name,int score)
{
  CURLcode ret;
  CURL *hnd;

  char url[128];

  hnd = curl_easy_init();
  char* encoded_name=curl_easy_escape(curl,name,0);
  sprntft(url,"http://0.0.0.0:8080/post_score?score=%d&name=%d",score,encoded_name);
  curl_easy_setopt(hnd, CURLOPT_BUFFERSIZE, 102400L);
  curl_easy_setopt(hnd, CURLOPT_URL, url); // Post送信するURI, portによって変更する必要あり.
// curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, post_data); // Post送信で渡す際に指定するscore.
// curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "POST");
  
  ret = curl_easy_perform(hnd);

  curl_free(encoded_name);
  curl_easy_cleanup(hnd);
  hnd = NULL;

  return (int)ret;
}

char* get_score()
{
  CURLcode ret;
  CURL *hnd;
  struct Buffer *buf;

  buf = (struct Buffer *)malloc(sizeof(struct Buffer));
  buf->data = NULL;
  buf->data_size = 0;

  hnd = curl_easy_init();
  curl_easy_setopt(hnd, CURLOPT_BUFFERSIZE, 102400L);
  curl_easy_setopt(hnd, CURLOPT_URL, "http://0.0.0.0:8080/get_score"); 
  //curl_easy_setopt(hnd, CURLOPT_USERAGENT, "curl/7.68.0");

  curl_easy_setopt(hnd, CURLOPT_WRITEDATA, buf);
  curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, buffer_writer);


  ret = curl_easy_perform(hnd);

  curl_easy_cleanup(hnd);
  hnd = NULL;

//  printf("data=>%s\n", buf->data);
//  free(buf->data);
  char* result = buf->data;
  if(ret == CURLE_OK){
      buf->data[buf->data_size] = 0;
      result =  buf->data;
  } else {
      free(buf->data);
      result = NULL;
  }

  free(buf);

  return result;
}