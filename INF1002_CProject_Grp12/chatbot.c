/*
 * INF1002 (C Language) Group Project, 2022-23 Trimester 1
 *
 * This file implements the behaviour of the chatbot. The main entry point to
 * this module is the chatbot_main() function, which identifies the intent
 * using the chatbot_is_*() functions then invokes the matching chatbot_do_*()
 * function to carry out the intent.
 *
 * chatbot_main() and chatbot_do_*() have the same method signature, which
 * works as described here.
 *
 * Input parameters:
 *   inc      - the number of words in the question
 *   inv      - an array of pointers to each word in the question
 *   response - a buffer to receive the response
 *   n        - the size of the response buffer
 *
 * The first word indicates the intent. If the intent is not recognised, the
 * chatbot should respond with "I do not understand [intent]." or similar, and
 * ignore the rest of the input.
 *
 * If the second word may be a part of speech that makes sense for the intent.
 *    - for WHAT, WHERE and WHO, it may be "is" or "are".
 *    - for SAVE, it may be "as" or "to".
 *    - for LOAD, it may be "from".
 * The word is otherwise ignored and may be omitted.
 *
 * The remainder of the input (including the second word, if it is not one of the
 * above) is the entity.
 *
 * The chatbot's answer should be stored in the output buffer, and be no longer
 * than n characters long (you can use snprintf() to do this). The contents of
 * this buffer will be printed by the main loop.
 *
 * The behaviour of the other functions is described individually in a comment
 * immediately before the function declaration.
 *
 * You can rename the chatbot and the user by changing chatbot_botname() and
 * chatbot_username(), respectively. The main loop will print the strings
 * returned by these functions at the start of each line.
 */

#define _CRT_SECURE_NO_WARNINGS
#define SMALL_TALK_FILE
#define KNOWLEDGE_NODES
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "chat1002.h"


 /*
  * Get the name of the chatbot.
  *
  * Returns: the name of the chatbot as a null-terminated string
  */
const char *chatbot_botname() {

	return "John";

}


/*
 * Get the name of the user.
 *
 * Returns: the name of the user as a null-terminated string
 */
const char *chatbot_username() {

	return "Me";

}


/*
 * Get a answer to user input.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0, if the chatbot should continue chatting
 *   1, if the chatbot should stop (i.e. it detected the EXIT intent)
 */
int chatbot_main(int numofwords, char *inv[], char *answers, int n) {

	/* check for empty input */
	if (numofwords < 1) {
		snprintf(answers, n, "");
		return 0;
	}
	/* look for an intent and invoke the corresponding do_* function */
	if (chatbot_is_exit(inv[0]))
		return chatbot_do_exit(numofwords, inv, answers, n);
	else if (chatbot_is_load(inv[0]))
		return chatbot_do_load(numofwords, inv, answers, n);
	else if (chatbot_is_question(inv[0]))
        return  chatbot_do_question(numofwords, inv, answers, n);
	else if (chatbot_is_reset(inv[0]))
		return chatbot_do_reset(numofwords, inv, answers, n);
	else if (chatbot_is_save(inv[0]))
		return chatbot_do_save(numofwords, inv, answers, n);
	else {
		return chatbot_do_smalltalk(numofwords, inv, answers, n);
	}

}


/*
 * Determine whether an intent is EXIT.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "exit" or "quit"
 *  0, otherwise
 */
int chatbot_is_exit(const char *intent) {

	return compare_token(intent, "exit") == 0 || compare_token(intent, "quit") == 0 || compare_token(intent, "bye") == 0;

}


/*
 * Perform the EXIT intent.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after a question)
 */
int chatbot_do_exit(int numofwords, char *inv[], char *answers, int n) {

	snprintf(answers, n, "Goodbye World!");

	return 1;

}


/*
 * Determine whether an intent is LOAD.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "load"
 *  0, otherwise
 */
int chatbot_is_load(const char *intent) {

	//if intent is load
	if (compare_token(intent, "load") == 0) {
		return 1;
	}

	//otherwise
	return 0;

}


/*
 * Load a chatbot's knowledge base from a file.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after loading knowledge)
 */
int chatbot_do_load(int numofwords, char *inv[], char *answers, int n) {

	FILE* fileptr;
	int numoflines = 0;

	if ((fileptr = fopen(inv[1], "r")) == NULL) {// If input file cannot be found, it's NULL
		snprintf(answers, n, "%s not found. Please try again!", inv[1]);
	}
	else { // If file can be found
		numoflines = knowledge_read(fileptr);
		if (numoflines == -1) {// If there are invalid input in file
			snprintf(answers, n, "Invalid file.");
		}
		else {// Valid input in files
			snprintf(answers, n, "Read %d responses from %s", numoflines, inv[1]);
		}
	}
	return 0;
}


/*
 * Determine whether an intent is a question.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "what", "where", or "who"
 *  0, otherwise
 */
int chatbot_is_question(const char *intent) {

	//if intent is where, who or what
	if (compare_token(intent, "where") == 0 || compare_token(intent, "what") == 0 || compare_token(intent, "who") == 0) {
		return 1;
	}

	//otherwise
	return 0;

}


/*
 * Answer a question.
 *
 * inv[0] contains the the question word.
 * inv[1] may contain "is" or "are"; if so, it is skipped.
 * The remainder of the words form the entity.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after a question)
 */
int chatbot_do_question(int numberofwords, char *inv[], char *answers, int n) {

	//create crafted answer string
	char * crafted_answer = calloc(n, sizeof(char));
    char * answer_temp = calloc(n, sizeof(char));
	// check for heap overflow
	if (crafted_answer == NULL) {
		printf("Out of memory.\n");
		exit(1);
	}

	// create the entity object - array of strings
	char ** entity = (char **) calloc(numberofwords - 2, sizeof(char *));

	// check for heap overflow
	if (entity == NULL) {
		printf("Out of memory.\n");
		exit(1);
	}
    int len_sentence=0;
    int array_size=0;

	//check if second word is 'is'/'are'


	if (compare_token(inv[1],"is")==0 || compare_token(inv[1],"are")==0) {



        for (int i = 0; i < numberofwords - 2; i++) { //taking all the values after entity [is]


            int length_of_str = strlen(inv[i + 2]) + 1;
            entity[i] = (char *) calloc(length_of_str, sizeof(char)); //allocate memory for individual strings
            if (entity[i] == NULL) { //check for heap overflow
                printf("Out of memory.\n");
                exit(1);
            }

            len_sentence = len_sentence + strlen(inv[i + 2]) + 1;// adding 1 to the end to take in account of spaces
            array_size++;
            strncpy(entity[i], inv[i + 2], length_of_str); //copy value from user input to entity
        }


        char *f_entity = (char *) calloc(len_sentence, sizeof(char));

        for (int j = 0; j < array_size; ++j) {

            strcat(f_entity, entity[j]);
            strcat(f_entity, " ");
        }
        f_entity[len_sentence] = '\0';
        f_entity[len_sentence - 1] = '\0';




        //gets return value from knowledge bank
        int knowledge_return = knowledge_get(inv[0], f_entity, answers, n);
        switch (knowledge_return) {
            case KB_NOTFOUND: //if cannot find intent
                strcat(answer_temp, chatbot_botname());
                strcat(answer_temp, ": I don't know."); //copy values to buffer
                for (int i = 0; i < numberofwords; i++) {
                    strcat(answer_temp, " ");
                    strcat(answer_temp, inv[i]);
                }
                strcat(answer_temp, "?");
				printf("%s",answer_temp);



              int kout = knowledge_put(inv[0],f_entity,answers,n);

                strcat(crafted_answer, "Thank you"); //copy values to buffer
                snprintf(answers, n, "%s", crafted_answer);
                return kout;



			case KB_OK:


            default:
                break;
        }

        return 0;
    }else{
		strcat(crafted_answer, "Please include is/are in your question."); //copy values to buffer
		snprintf(answers, n, "%s", crafted_answer); //put this to response

		return 0;
	}


}


/*
 * Determine whether an intent is RESET.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "reset"
 *  0, otherwise
 */
int chatbot_is_reset(const char *intent) {

	//if intent is reset
	if (compare_token(intent, "reset") == 0) {
		return 1;
	}

	//otherwise
	return 0;

}


/*
 * Reset the chatbot.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after beign reset)
 */
int chatbot_do_reset(int numofwords, char *inv[], char *answers, int n) {

	knowledge_reset();
	// Return print statement
	snprintf(answers, n, "%s reset!", chatbot_botname());


	return 0;

}


/*
 * Determine whether an intent is SAVE.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "save"
 *  0, otherwise
 */
int chatbot_is_save(const char *intent) {

	//if intent is save
	if (compare_token(intent, "save") == 0) {
		return 1;
	}

	//otherwise
	return 0;

}


/*
 * Save the chatbot's knowledge to a file.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after saving knowledge)
 */
int chatbot_do_save(int numofwords, char *inv[], char *answers, int n) {

	// int inc = number of words in user input = FILENAME
	// char *inv[] = pointers to the beginning of each word of input = pointer to FILENAME
	// char *response = buffer to receive the response = for printing out result
	// int n = the maximum number of characters to write to the response buffer

	/* to be implemented */
	char filename[MAX_INPUT];
	char *token;
	const char s[2] = ".";
	FILE * f;

	if (compare_token(inv[1], "as") == 0 || compare_token(inv[1], "to") == 0) {
		strcpy(filename, inv[2]);
	}
	else {
		strcpy(filename, inv[1]);
	}

	if (strrchr(filename, '.') != NULL) {
		if (strrchr(filename, '.') != ".ini") {
			token = strtok(filename, s);				// gets first token
			strcpy(filename, strcat(token, ".ini"));	// replaces extension with .ini
		}
	}
	else {
		strcpy(filename, strcat(filename, ".ini"));		//appends .ini extension to filename
	}


	if (what_intent->next != NULL || who_intent->next != NULL || where_intent->next != NULL) {
		f = fopen(filename, "w");
		if (f == NULL) {
			snprintf(answers, n, "Error opening file");
			return 0;
		}
		knowledge_write(f);
		snprintf(answers, n, "My knowledge has been saved to %s", filename);
		fclose(f);
	}
	else {
		snprintf(answers, n, "Knowledge Base is empty! Sad... Please try again!");
		return 0;
	}
}



/*
 * Respond to smalltalk.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0, if the chatbot should continue chatting
 *   1, if the chatbot ran out of responses for some reason (and should theoretically never come here)
 */
int chatbot_do_smalltalk(int numofwords, char *inv[], char *answers, int n) {

	/* Initialize local variables to be used*/
	int index_of_word; //index of word found in inv
	int index_of_keyword; //index of hardcoded keyword
	int * returnarray = calloc(2, sizeof(int)); //return array to retrieve position of indexes from findpos

	if (returnarray == NULL) {
		printf("Out of memory.\n");
		exit(1);
	}

	//create crafted answer string
	char * crafted_answer = calloc(n, sizeof(char));

	// check for heap overflow
	if (crafted_answer == NULL) {
		printf("Out of memory.\n");
		exit(1);
	}

	/* create temp input to put to lowercase in order to match with chatbot words */
	char ** temporary_input = (char **)calloc(numofwords, sizeof(char *));

	for (int word_index = 0; word_index < numofwords; word_index++) { //iterate through to put all to words to lower case
		temporary_input[word_index] = (char *)calloc(30, sizeof(char)); //allocate memory for individual strings (max value 30)
		strncpy(temporary_input[word_index], inv[word_index], 30); //copy inv value to temp_input
		for (int char_index = 0; char_index < strlen(inv[word_index]); char_index++) {
			temporary_input[word_index][char_index] = tolower(temporary_input[word_index][char_index]); //lowercase
		}
	}

	memcpy(returnarray, findpos(numofwords, temporary_input), sizeof(int)*2); //copy the results from findpos to return array
	index_of_word = returnarray[0];
	index_of_keyword = returnarray[1];

	strncpy(crafted_answer, responses[index_of_keyword][replycount[index_of_keyword] % responsesperkeyword[index_of_keyword]], n);
	// copies the response based on keyword to crafted response

	if (crafted_answer[strlen(crafted_answer) - 1] == '*') {
		// strip * from the response
		crafted_answer[strcspn(crafted_answer, "*")] = 0;

		// swaps all other words with appropriate responses
		for (int after_keyword = index_of_word + 1; after_keyword < numofwords; after_keyword++) { //iterate through rest of words
			for (int swap_index = 0; swap_index < SWAP_TOTAL; swap_index++) { //iterate through swap list
				if (strcmp(temporary_input[after_keyword], swaps[swap_index][0]) == 0) {
					temporary_input[after_keyword] = (char *)swaps[swap_index][1]; //swap word
				}
			}
			strcat(crafted_answer, " ");
			strcat(crafted_answer, temporary_input[after_keyword]); //formats and puts word into crafted response
		}

	}


	snprintf(answers, n, "%s", crafted_answer); //put this to response

	replycount[index_of_keyword]++; //increment to get a different response from same category

	return 0;

}


/*
 * Creates the arrays to be used in smalltalk
 *
 *	Input:
 *  inc - number of strings
 *	temp_input - input strings
 *
 * Returns:
 *   int *, position of word and position of keyword
 */
int * findpos(int numofwords, char ** temporary_input) {

	//creates local variables for this function
	int index_of_keyword = KEYWORDS_TOTAL - 1;
	int index_of_word = -1;
	int * returnarray = malloc(2 * sizeof(int));
	if (returnarray == NULL) {
		printf("Out of memory.\n");
		exit(1);
	}

	returnarray[0] = index_of_word;
	returnarray[1] = index_of_keyword;

	for (int keyword_index = 0; keyword_index < KEYWORDS_TOTAL; keyword_index++) {
		for (int word_index = 0; word_index < numofwords; word_index++) {

			//create string to checked with for 2 words
			char * two_chk_string = calloc(30, sizeof(char));

			// check for heap overflow
			if (two_chk_string == NULL) {
				printf("Out of memory.\n");
				exit(1);
			}

			//create string to checked with for 3 words
			char * three_chk_string = calloc(30, sizeof(char));

			// check for heap overflow
			if (three_chk_string == NULL) {
				printf("Out of memory.\n");
				exit(1);
			}

			//if there can be phrase of 2 words formed, combine them together
			int max_index_two = word_index + 2; //check if a phrase of 2 char from point of index will not exceed word array range
			if (max_index_two < numofwords) {
				strncpy(two_chk_string, temporary_input[word_index], sizeof(temporary_input[word_index]));
				strcat(two_chk_string, " ");
				strcat(two_chk_string, temporary_input[word_index + 1]);
			}

			//if there can be phrase of 3 words formed, combine them together
			int max_index_three = word_index + 3; //check if a phrase of 3 char from point of index will not exceed word array range
			if (max_index_three < numofwords) {
				strncpy(three_chk_string, temporary_input[word_index], sizeof(temporary_input[word_index]));
				strcat(three_chk_string, " ");
				strcat(three_chk_string, temporary_input[word_index + 1]);
				strcat(three_chk_string, " ");
				strcat(three_chk_string, temporary_input[word_index + 2]);
			}

			if (strcmp(three_chk_string, keywords[keyword_index]) == 0) { //if there are a list of 3 words in inv that matches a hardcoded keyword
				returnarray[0] = max_index_three - 1; //set word index as a var, minus 1 to position it properly in array
				returnarray[1] = keyword_index; //set keyword index as a var
				return returnarray;
			}
			else if (strcmp(two_chk_string, keywords[keyword_index]) == 0) { //if there are a list of 2 words in inv that matches a hardcoded keyword
				returnarray[0] = max_index_two - 1;
				returnarray[1] = keyword_index;
				return returnarray;
			}
			else if (strcmp(temporary_input[word_index], keywords[keyword_index]) == 0) { //if there is a word in inv that matches a hardcoded keyword
				returnarray[0] = word_index;
				returnarray[1] = keyword_index;
				return returnarray;
			}
		}
	}

	return returnarray;
}

/*
 * Creates the arrays to be used in smalltalk
 *
 *
 *
 * Returns:
 *   NULL
 */
void init_keywordcounters() {
	replycount = calloc(KEYWORDS_TOTAL, sizeof(int)); //allocate memory for int *
	if (replycount == NULL) { //if cannot allocate memory
		printf("Out of Memory. Bye");
		exit(1); //exit unhappily
	}
}
