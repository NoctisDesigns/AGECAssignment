#include <stdio.h>
#include <stdlib.h>
#include "Commons.h"
#include "3DSLoader.h"
#include <sys\stat.h>

long filelength(int f)
{
	struct stat buf;

	fstat(f, &buf);

	return(buf.st_size);
}

char Load3DS(obj_type_ptr p_object, char *p_filename)
{
	int i;															//Index variable
	FILE *inFile;													//File pointer

	unsigned short chunkId, s_temp;									//Chunk identifier
	int chunkLength;												//Chunk length
	unsigned char name;												//Char variable
	unsigned short size;											//# of elements in each chunk

	unsigned short faceFlag;										//Flag that stores some face information

	if ((inFile = fopen(p_filename, "rb")) == NULL)					//Open the file
		return 0;

	while (ftell(inFile) < filelength(fileno(inFile)))				//Loop to scan the whole 3DS file
	{
		fread(&chunkId, 2, 1, inFile);								//Read the chunk header
		fread(&chunkLength, 4, 1, inFile);							//Read the chunk length

		switch (chunkId)
		{
		case 0x4d4d:												//MAIN3DS: Main chunk
			break;													//Contains all the other chunks with the ID 4d4d

		case 0x3d3d:												//EDIT3DS: 3D editor chunk
			break;													//Chunks with the object's layout information with the ID 3d3d

		case 0x4000:												//EDIT OBJECT: Object block
			i = 0;													//Information for each object with the ID 4000
			do
			{
				fread(&name, 1, 1, inFile);
				p_object->name[i] = name;
				i++;
			} while (name != '\0' && i < 20);
			break;

		case 0x4100:												//OBJ TRIMESH: Trianglar mesh
			break;													//Contains chunks for 3D mesh info with the ID 4100

		case 0x4110:
			fread(&size, sizeof(unsigned short), 1, inFile);		//TRI VERTEXL: Vertices list
			p_object->vertices_qty = size;							//ID 4110

			for (i = 0; i < size; i++)
			{
				fread(&p_object->vertex[i].x, sizeof(float), 1, inFile);
				fread(&p_object->vertex[i].y, sizeof(float), 1, inFile);
				fread(&p_object->vertex[i].z, sizeof(float), 1, inFile);
			}
			break;

		case 0x4120:												//TRI FACEL
			fread(&size, sizeof(unsigned short), 1, inFile);		//Contains triangles faces list with ID 4120
			p_object->triangles_qty = size;

			for (i = 0; i < size; i++)
			{
				fread(&s_temp, sizeof(unsigned short), 1, inFile);
				p_object->triangles[i].a = s_temp;

				fread(&s_temp, sizeof(unsigned short), 1, inFile);
				p_object->triangles[i].b = s_temp;

				fread(&s_temp, sizeof(unsigned short), 1, inFile);
				p_object->triangles[i].c = s_temp;

				fread(&faceFlag, sizeof(unsigned short), 1, inFile);
			}
			break;

		case 0x4140:
			fread(&size, sizeof(unsigned short), 1, inFile);
			for (i = 0; i < size; i++)
			{
				fread(&p_object->mapcoord[i].u, sizeof(float), 1, inFile);
				fread(&p_object->mapcoord[i].v, sizeof(float), 1, inFile);
			}
			break;

		default:
			fseek(inFile, chunkLength - 6, SEEK_CUR);
		}
	}

	fclose(inFile);
	return(1);
}