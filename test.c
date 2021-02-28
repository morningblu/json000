#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"


typedef struct
{
	char software_ver[48];
	char update_info[2048];
	char signed_url[512];
	char file_name[128];
	int file_size;

}verResInfo;


int ParseInfo(char* jsonStr, verResInfo* info)
{
	int ret = 0;
	cJSON* root = NULL;
	cJSON* object = NULL;
	cJSON* item = NULL;

	do
	{
		if (NULL == jsonStr || NULL == info)
		{
			printf("input param is NULL");
			ret = -1;
			break;
		}

		root = cJSON_Parse(jsonStr);
		if (NULL == root)
		{
			printf("failed Parse jason [%s] \n", cJSON_GetErrorPtr());
			ret = -1;
			break;
		}
		else
		{
			//有格式打印
			printf("%s\n\n", cJSON_Print(root));
			//无格式打印
			printf("%s\n\n", cJSON_PrintUnformatted(root));
		}

		object = cJSON_GetObjectItem(root, "software");
		if (NULL == object)
		{
			printf("failed to get object [software] \n");
			ret = -1;
			break;
		}

		item = cJSON_GetObjectItem(object, "software_ver");
		if (NULL != item && NULL != item->valuestring)
		{
			if (sizeof(info->software_ver) > strlen(item->valuestring))
			{
				memcpy(info->software_ver, item->valuestring, strlen(item->valuestring));
			}
			else
			{
				printf("buffer length is not enough . [%d] [%d]", sizeof((info)->software_ver), strlen(item->valuestring));
			}
		}
		else
		{
			printf("item or item value is NULL");
		}

		item = cJSON_GetObjectItem(object, "update_info");
		if (NULL != item && NULL != item->valuestring)
		{
			if (sizeof(info->update_info) > strlen(item->valuestring))
			{
				memcpy(info->update_info, item->valuestring, strlen(item->valuestring));
			}
			else
			{
				printf("buffer length is not enough . [%d] [%d]", sizeof(info->update_info), strlen(item->valuestring));
			}
		}
		else
		{
			printf("item or item value is NULL");
		}

		item = cJSON_GetObjectItem(object, "signed_url");
		if (NULL != item && NULL != item->valuestring)
		{
			if (sizeof(info->signed_url) > strlen(item->valuestring))
			{
				memcpy(info->signed_url, item->valuestring, strlen(item->valuestring));
			}
			else
			{
				printf("buffer length is not enough . [%d] [%d]", sizeof(info->signed_url), strlen(item->valuestring));
			}
		}
		else
		{
			printf("item or item value is NULL");
		}

		item = cJSON_GetObjectItem(object, "file_name");
		if (NULL != item && NULL != item->valuestring)
		{
			if (sizeof(info->file_name) > strlen(item->valuestring))
			{
				memcpy(info->file_name, item->valuestring, strlen(item->valuestring));
			}
			else
			{
				printf("buffer length is not enough . [%d] [%d]", sizeof(info->file_name), strlen(item->valuestring));
			}
		}
		else
		{
			printf("item or item value is NULL");
		}

		item = cJSON_GetObjectItem(object, "file_size");
		if (NULL != item)
		{
			info->file_size = item->valueint;
		}
		else
		{
			printf("item is NULL");
		}

	} while (0);

	return ret;
}


void printJson(cJSON * root)//以递归的方式打印json的最内层键值对
{
	for (int i = 0; i<cJSON_GetArraySize(root); i++) //遍历最外层json键值对
	{
		cJSON * item = cJSON_GetArrayItem(root, i);
		if (cJSON_Object == item->type) //如果对应键的值仍为cJSON_Object就递归调用printJson
			printJson(item);
		else //值不为json对象就直接打印出键和值
		{
			printf("%s->", item->string);
			printf("%s\n", cJSON_Print(item));
		}
	}
}

int main()
{
	char * jsonStr = "{\"semantic\":{\"slots\":{\"name\":\"张三\"}}, \"rc\":0, \"operation\":\"CALL\", \"service\":\"telephone\", \"text\":\"打电话给张三\"}";
	cJSON * root = NULL;
	cJSON * item = NULL;//cjson对象
	char* jasonString ="{\"software\": {\"software_ver\": \"A2.00\",\"update_info\":\"123\",\"signed_url\":\"http\",\"file_name\":\"zip\",\"file_size\":1234,\"last_modefied\":\"2021\"}}";
	
	
	verResInfo ver = {0};
	ParseInfo(jasonString, &ver);
	root = cJSON_Parse(jsonStr);
	if (!root)
	{
		printf("Error before: [%s]\n", cJSON_GetErrorPtr());
	}
	else
	{
		printf("%s\n", "有格式的方式打印Json:");
		printf("%s\n\n", cJSON_Print(root));
		printf("%s\n", "无格式方式打印json：");
		printf("%s\n\n", cJSON_PrintUnformatted(root));

		printf("%s\n", "一步一步的获取name 键值对:");
		printf("%s\n", "获取semantic下的cjson对象:");
		item = cJSON_GetObjectItem(root, "semantic");//
		printf("%s\n", cJSON_Print(item));
		printf("%s\n", "获取slots下的cjson对象");
		item = cJSON_GetObjectItem(item, "slots");
		printf("%s\n", cJSON_Print(item));
		printf("%s\n", "获取name下的cjson对象");
		item = cJSON_GetObjectItem(item, "name");
		printf("%s\n", cJSON_Print(item));

		printf("%s:", item->string); //看一下cjson对象的结构体中这两个成员的意思
		printf("%s\n", item->valuestring);


		printf("\n%s\n", "打印json所有最内层键值对:");
		printJson(root);
	}
	return 0;
}