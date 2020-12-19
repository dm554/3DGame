#include <stdio.h>
#include "simple_json.h"
#include "simple_json_object.h"
#include "file_handler.h"

void get_float(char *path, char *key, float *floatvariable){
	SJson *jsobject;
	SJson *value;
	
	jsobject = sj_load(path);
	value = sj_object_get_value(jsobject, key);
	sj_get_float_value(value, floatvariable);

}