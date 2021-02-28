#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char uchar;

uchar* Base64_encode(uchar* input)
{
	int inLen = 0u;
	int outLen = 0u;
	uchar* output = NULL;
	int inIdx = 0u;
	int outIdx = 0u;

	uchar tmp[3] = { 0 };


	uchar * base64_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

	if (NULL == input)
	{
		return NULL;
	}

	/* step1. calculate encode length */
	inLen = strlen(input);
	if (inLen % 3 == 0)
	{
		outLen = inLen / 3 * 4;
	}
	else
	{
		outLen = (inLen / 3 + 1) * 4;
	}

	/* step2. malloc encode buffer */
	output = (uchar *)malloc(sizeof(uchar) * (outLen + 1));
	if (NULL == output)
	{
		return NULL;
	}
	memset(output, 0x0, outLen + 1);

	/* step3. encode */
	while(inLen - inIdx >= 3)
	{
		uchar *p = input + inIdx;
		output[outIdx++] = base64_table[ p[0] >> 2];
		output[outIdx++] = base64_table[((p[0] << 4) & 0x30) | ((p[1] >> 4) & 0x0F)];
		output[outIdx++] = base64_table[((p[1] << 2) & 0x3C) | ((p[2] >> 6) & 0x03)];
		output[outIdx++] = base64_table[p[2] & 0x3F];
		inIdx += 3;
	}
	if (inLen - inIdx == 1)
	{
		uchar *p = input+ inIdx;
		output[outIdx++] = base64_table[p[0] >> 2];
		output[outIdx++] = base64_table[(p[0] << 4) & 0x30];
		output[outIdx++] = '=';
		output[outIdx++] = '=';
	}
	else if (inLen - inIdx == 2)
	{
		uchar *p = input + inIdx;
		output[outIdx++] = base64_table[p[0] >> 2];
		output[outIdx++] = base64_table[((p[0] << 4) & 0x30) | ((p[1] >> 4) & 0x0F)];
		output[outIdx++] = base64_table[(p[1] << 2) & 0x3C];
		output[outIdx++] = '=';
	}

	return output;
}

int main()
{
	printf("%s",Base64_encode("this is a example"));
}
