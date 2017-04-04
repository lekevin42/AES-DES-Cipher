#include <string>
#include "CipherInterface.h"
#include "DES.h"
#include "AES.h"
#include <fstream>
#include <stdio.h>

#include <iostream>

using namespace std;

void choose_cipher(string cipher_name, char* key, string option, string input_file, string output_file);

void choose_AES(char* key, string option, string input_file, string output_file);

int main(int argc, char** argv)
{
	string cipher_name;
	char* key;
	string option;
	string input_file;
	string output_file;
	
	if (argc == 6){
		cipher_name = argv[1];
		key = argv[2];
		option = argv[3];
		input_file = argv[4];
		output_file = argv[5];
	}
	else{
		cout << "Usage: ./cipher <key> <option> <input_file> <output_file>" << endl;
		exit(-1);
	}
	

	choose_cipher(cipher_name, key, option, input_file, output_file);
	
	
	return 0;
}

void choose_cipher(string cipher_name, char* key, string option, string input_file, string output_file){	
	if (cipher_name == "AES"){
		choose_AES(key, option, input_file, output_file);
	}
	
	else if (cipher_name == "DES"){
		
	}
		
	else{
		cout << "Invalid option. Choose <AES/DES>!" << endl;
		exit(-1);
		
	}
}


void choose_AES(char* key , string option, string input_file, string output_file){
	CipherInterface* cipher = new AES();
	FILE* infile = fopen(input_file.c_str(), "r");
	FILE* outfile = fopen(output_file.c_str(), "w");
	unsigned char* block = new unsigned char[16];
	
	if(!cipher)
	{
		fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",	
		__FILE__, __FUNCTION__, __LINE__);
		exit(-1);
	}
	
	if (infile == NULL){
		cout << "File " << input_file << " could not be opened" << endl;
		exit(-1);
	}
	
	if (outfile == NULL){
		cout << "File " << output_file << " could not be opened" << endl;
		exit(-1);
	}
	
	if (option == "ENC"){
		if (!cipher->setKey((unsigned char*)key)){
			fprintf(stderr, "AES_set_encrypt_key() failed!\n");
		}

		int count_bytes = 0;
		
		while (count_bytes = fread(block, 1, 16, infile)){
			while (count_bytes < 16){
				block[count_bytes] = '0';
				count_bytes++;	
				
			}
			block = cipher->encrypt(block);
			fwrite(block, 1, 16, outfile);
		}
		
	}
			
	else if (option == "DEC"){
		if (!cipher->setKey((unsigned char*)key)){
			fprintf(stderr, "AES_set_decrypt_key() failed!\n");
		}
			
		int padding = 15;
		while (fread(block, 1, 16, infile)){
			block = cipher->decrypt(block);


			fwrite(block, 1, 16, outfile);
		}	
	}
	
	else{
		cout << "Error option was not <ENC/DEC>" << endl;
		exit(-1);
	}
	
	fclose(infile);
	fclose(outfile);
	
	delete block;
	delete cipher;
}
