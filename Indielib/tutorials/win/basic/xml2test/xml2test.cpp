// xml2test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "tinyxml.h"

void dump_to_stdout(TiXmlDocument* doc)
{
	printf("%s\n",doc->FirstChildElement()->Value());
	//printf("%s\n",doc->FirstChildElement()->FirstChildElement()->Value());
	TiXmlElement * elem = doc->FirstChildElement();
	for(TiXmlElement* e = elem->FirstChildElement(); e != NULL; e = e->NextSiblingElement()){
		printf("%s\n",e->Value());
		TiXmlNode*f = e->FirstChildElement();
		for(; f != NULL; f = f->NextSiblingElement()){
				printf("+%s\n",f->Value());
		}
		const char * word = e->Attribute("x");
		if(word != NULL){
			printf("+%s\n",word);
		}
		//TiXmlText* text = e->ToText();
		//if(text == NULL)
		//	continue;
		//string t = text->Value();
		// Do stuff
	}
	//printf("%s\n",doc->FirstChildElement()->FirstChildElement()->Value());
}

// load the named file and dump its structure to STDOUT
void dump_to_stdout(const char* pFilename)
{
	TiXmlDocument doc(pFilename);
	bool loadOkay = doc.LoadFile();
	if (loadOkay)
	{
		printf("\n%s:\n", pFilename);
		dump_to_stdout( &doc ); // defined later in the tutorial
	}
	else
	{
		printf("Failed to load file \"%s\"\n", pFilename);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	printf("hello world\n");
	TiXmlDocument doc( "test.xml" );
	doc.LoadFile();
	dump_to_stdout( &doc );
	for(;;);
	return 0;
}

