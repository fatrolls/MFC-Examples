#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static const int BUFFER_SIZE = 1 * 1024;
static const char define_str[] = "#define";
static const char hex_str[] = "0x";
static const char _APS_NEXT_RESOURCE_VALUE[] = "_APS_NEXT_RESOURCE_VALUE";
static const char _APS_NEXT_COMMAND_VALUE[] = "_APS_NEXT_COMMAND_VALUE";
static const char _APS_NEXT_CONTROL_VALUE[] = "_APS_NEXT_CONTROL_VALUE";
static const char _APS_NEXT_SYMED_VALUE[] = "_APS_NEXT_SYMED_VALUE";
static const char IDR_[] = "IDR_";
static const char ID_[] = "ID_";
static const char IDS_[] = "IDS_";
static const char IDC_[] = "IDC_";
static const char AFX_[] = "AFX_";
static const char in_name[] = "resource.h";
static const char out_name[] = "$rcremap.tmp";
static const char bak_name[] = "resource.bak";
static const char inf_name[] = "resource.inf";

static const char id_name[] = "ID";
static const char ids_name[] = "IDS";
static const char idc_name[] = "IDC";

static int idc_low_limit = 1000;
static int id_low_limit = 33000;
static int ids_low_limit = 10000;

static int idc_low_limit_first;
static int id_low_limit_first;
static int ids_low_limit_first;

static void read_inf(const char* buffer)
{
	while (*buffer && isspace(*buffer))
		++buffer;

	int* pi;
	if (strnicmp(buffer, idc_name, strlen(idc_name)) == 0)
		pi  = &idc_low_limit;
	else if (strnicmp(buffer, ids_name, strlen(ids_name)) == 0)
		pi  = &ids_low_limit;
	else if (strnicmp(buffer, id_name, strlen(id_name)) == 0)
		pi  = &id_low_limit;
	else 
		return ;

	while (*buffer && !isdigit(*buffer))
		++buffer;

	*pi = atoi(buffer);
	return ;
}

static void read_inf()
{
	FILE* in = fopen(inf_name,"rt");
	if (in == NULL)
		return ;

	char buffer[1024];
	while (fgets(buffer, sizeof(buffer), in) != NULL)
		read_inf(buffer);

	fclose(in);
	return ;
}

static void write_inf()
{
	FILE* out = fopen(inf_name,"wt");
	if(out == NULL)
	{
		printf("Error creating configuration file\n");
		return ;
	}
	fprintf(out, "%-4.4s = %ld\n", idc_name,	idc_low_limit_first);
	fprintf(out, "%-4.4s = %ld\n", ids_name,	ids_low_limit_first);
	fprintf(out, "%-4.4s = %ld\n", id_name,	id_low_limit_first);
	fclose(out);
	return ;
}


static char* trim(char* buffer)
{
	char* ptr = buffer;
	while(isspace(*ptr))
		ptr++;
	strrev(ptr);
	while(isspace(*ptr))
		ptr++;
	strrev(ptr);
	strcpy(buffer,ptr);
	return buffer;
}

static int is_define(const char* ptr, char* name, int& value)
{
	char buffer[BUFFER_SIZE];
	strcpy(buffer, ptr);
	char* buf_ptr = trim(buffer);

	if (strncmp(buf_ptr, define_str, strlen(define_str)) != 0)
		return 0;

	buf_ptr += strlen(define_str);

	while(isspace(*buf_ptr))
		buf_ptr++;

	while (*buf_ptr != '\0' && !isspace(*buf_ptr))
		*name++ = *buf_ptr++;

	*name = '\0';
	while(isspace(*buf_ptr))
		buf_ptr++;

	if (strnicmp(buf_ptr, hex_str, strlen(hex_str)) == 0)
		return 0;

	value = atoi(buf_ptr);
	return 1;
}

static void write_define(FILE* file, const char* name, int value)
{
 int len = 40 - strlen(name) - 1 - strlen(define_str);
 if (len <= 0)
	 len = 1;

	fprintf(file, "%s %s%*s%ld\n", 
		define_str,
		name, 
		len,
		"",
		value);
	printf("%s %s%*s%ld\n", 
		define_str,
		name, 
		len,
		"",
		value);
}

void main(int argc,char *argv[])
{
	printf("\nRemap .RC identifiers\n");
	printf("\nUsage: RCREMAP [idc_low_limit] [ids_low_limit] [id_low_limit]\n\n\n");

	FILE* out = fopen(out_name,"wt");
	if(out == NULL)
	{
		printf("Error creating file\n");
		return ;
	}

	FILE* in = fopen(in_name,"rt");
	if (in == NULL)
	{
		fclose(out);
		remove(out_name);
		printf("Error opening file\n");
		return ;
	}

	read_inf();

	if (argc >= 2)
		idc_low_limit = atoi(argv[1]);
	if (argc >= 3)
		ids_low_limit = atoi(argv[2]);
	if (argc >= 4)
		id_low_limit = atoi(argv[3]);

	ids_low_limit = (ids_low_limit / 16) * 16;

	printf("IDC = %ld\n", idc_low_limit);
	printf("IDS = %ld\n", ids_low_limit);
	printf("ID  = %ld\n\n", id_low_limit);

	idc_low_limit_first = idc_low_limit;
	id_low_limit_first = id_low_limit;
	ids_low_limit_first = ids_low_limit;

	int ids_base = -1;

	char buffer[BUFFER_SIZE];
	while(fgets(buffer, sizeof(buffer), in) != NULL)
	{
		char name[BUFFER_SIZE];
		int value;
		if (!is_define(buffer, name, value))
		{
			fputs(buffer, out);
			fputs(buffer, stdout);
		}
		else if (stricmp(name, _APS_NEXT_RESOURCE_VALUE) == 0 ||
			stricmp(name, _APS_NEXT_CONTROL_VALUE) == 0 ||
			stricmp(name, _APS_NEXT_SYMED_VALUE) == 0)
		{
			write_define(out, name, idc_low_limit + 1);
		}
		else if (stricmp(name, _APS_NEXT_COMMAND_VALUE) == 0)
		{
			write_define(out, name, id_low_limit + 1);
		}
		else if (strnicmp(name, AFX_, strlen(AFX_)) == 0)
		{
			fputs(buffer, out);
			fputs(buffer, stdout);
		}
		else if (strnicmp(name, IDR_, strlen(IDR_)) == 0)
		{
			fputs(buffer, out);
			fputs(buffer, stdout);
		}
		else if (strnicmp(name, IDS_, strlen(IDS_)) == 0)
		{
			if (ids_base < 0)
			{
				ids_base = value;
				ids_base = (ids_base / 16) * 16;
			}
			write_define(out, name, ids_low_limit + value - ids_base);
		}
		else if (strnicmp(name, IDC_, strlen(IDC_)) == 0)
		{
			write_define(out, name, idc_low_limit++);
		}
		else if (strnicmp(name, ID_, strlen(ID_)) == 0)
		{
			write_define(out, name, id_low_limit++);
		}
		else
		{
			write_define(out, name, idc_low_limit++);
		}
	}
	fclose(in);
	fclose(out);

	remove(bak_name);
	rename(in_name, bak_name);
	rename(out_name, in_name);

	write_inf();

	return ;
}

