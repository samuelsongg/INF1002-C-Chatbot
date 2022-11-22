/*
 * INF1002 (C Language) Group Project, 2022-23 Trimester 1
 *
 * This file implements the chatbot's knowledge base.
 *
 * knowledge_get() retrieves the response to a question.
 * knowledge_put() inserts a new response to a question.
 * knowledge_read() reads the knowledge base from a file.
 * knowledge_reset() erases all of the knowledge.
 * kowledge_write() saves the knowledge base in a file.
 *
 * You may add helper functions as necessary.
 */

#define KNOWLEDGE_NODES
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "chat1002.h"


/*
 * Get the response to a question.
 *
 * Input:
 *   intent   - the question word
 *   entity   - the entity
 *   response - a buffer to receive the response
 *   n        - the maximum number of characters to write to the response buffer
 *
 * Returns:
 *   KB_OK, if a response was found for the intent and entity (the response is copied to the response buffer)
 *   KB_NOTFOUND, if no response could be found
 *   KB_INVALID, if 'intent' is not a recognised question word
 */
int knowledge_get(const char *intent, char *entity, char *answers, int n) {


    if (compare_token(intent, "who") == 0) {


        char *crafted_answer = calloc(n, sizeof(char));

        if (who_intent->next != NULL) {

            EntityNode *head = who_intent->next;

            head = Entitysearch_list(head, entity);

            if (head != NULL) {

                strcat(crafted_answer, head->answers);
                snprintf(answers, n, "%s", crafted_answer);
                return KB_OK;

            } else {
                return KB_NOTFOUND;
            }


        } else {
            return KB_NOTFOUND;
        }


    } else if (compare_token(intent, "what") == 0) {


        char *crafted_answer = calloc(n, sizeof(char));

        if (what_intent->next != NULL) {

            EntityNode *head = what_intent->next;

            head = Entitysearch_list(head, entity);

            if (head != NULL) {

                strcat(crafted_answer, head->answers);
                snprintf(answers, n, "%s", crafted_answer);
                return KB_OK;

            } else {
                return KB_NOTFOUND;
            }


        } else {
            return KB_NOTFOUND;
        }


    } else if (compare_token(intent, "where") == 0) {
        char *crafted_answer = calloc(n, sizeof(char));

        if (where_intent->next != NULL) {

            EntityNode *head = where_intent->next;

            head = Entitysearch_list(head, entity);

            if (head != NULL) {

                strcat(crafted_answer, head->answers);
                snprintf(answers, n, "%s", crafted_answer);
                return KB_OK;

            } else {
                return KB_NOTFOUND;
            }


        } else {
            return KB_NOTFOUND;
        }


    } else {
        return KB_INVALID;
    }


}


/*
 * Insert a new response to a question. If a response already exists for the
 * given intent and entity, it will be overwritten. Otherwise, it will be added
 * to the knowledge base.
 *
 * Input:
 *   intent    - the question word
 *   entity    - the entity
 *   response  - the response for this question and entity
 *
 * Returns:
 *   KB_FOUND, if successful
 *   KB_NOMEM, if there was a memory allocation failure
 *   KB_INVALID, if the intent is not a valid question word
 */
int knowledge_put(const char *intent, const char *entity, const char *answer, int n) {

    /* to be implemented */
    char user_answer[MAX_INPUT];

    prompt_user(user_answer, n, "");

    char *tempChar = calloc(strlen(user_answer) + 1, sizeof(char));
    strncpy(tempChar, user_answer, sizeof(char) * strlen(user_answer) + 1);


    if (compare_token(intent, "who") == 0) {

        EntityNode *head = EntityCreate_node((char *) entity, tempChar);

        if (who_intent->next == NULL) {
            who_intent->next = head;
        } else {
            Entity_insert_at_tail(who_intent->next, head);
        }
        return KB_OK;
    } else if (compare_token(intent, "what") == 0) {
        EntityNode *head = EntityCreate_node((char *) entity, tempChar);

        if (what_intent->next == NULL) {
            what_intent->next = head;
        } else {
            Entity_insert_at_tail(what_intent->next, head);
        }

        return KB_OK;
    } else if (compare_token(intent, "where") == 0) {
        EntityNode *head = EntityCreate_node((char *) entity, tempChar);

        if (where_intent->next == NULL) {
            where_intent->next = head;
        } else {
            Entity_insert_at_tail(where_intent->next, head);
        }
        return KB_OK;
    } else {
        return KB_INVALID;
    }


}


/*
 * Read a knowledge base from a file.
 *
 * Input:
 *   f - the file
 *
 * Returns: the number of entity/response pairs successful read from the file
 */
int knowledge_read(FILE *f) {

	char sentence[MAX_INPUT];
	char delim[] = "=";
	char name[MAX_INPUT], value[MAX_INPUT], *tokens[MAX_INPUT];;
	int INTENT_FLAG = 0, linecount = 0;

	while (fgets(sentence, sizeof sentence, f) != NULL) /* read a sentence */ {

		int ERROR_FLAG = 1;


		sentence[strcspn(sentence, "\n")] = 0;// Remove trailing newsentence

		if (strcmp("[what]", sentence) == 0){
			INTENT_FLAG = 1;// Indicate it is reading sentences under the intent [What]
			continue;
		}
		if (strcmp("[where]", sentence) == 0){
			INTENT_FLAG = 2;// Indicate it is reading sentences under the intent [Where]
			continue;
		}
		if (strcmp("[who]", sentence) == 0){
			INTENT_FLAG = 3;// Indicate it is reading sentences under the intent [Who]
			continue;
		}

		// Checks if the delimiter '=' exists in sentence
		for (int i = 0; i < strlen(sentence); i++) {
			if (sentence[i] == '=') {
				ERROR_FLAG = 0;
			}
		}
		if (strcmp("", sentence) == 0) {// Check if its a blank sentence
			ERROR_FLAG = 0;
		}
		else {
			if (ERROR_FLAG == 1) {// Check if ERROR_FLAG is 1 (if delimiter does not exist in sentence)
				return -1; // Returns -1 (num_of_sentences in chatbot.c)
			}
			// Separate sentence by the delimiter '='
			tokens[0] = strtok(sentence, delim);// Get first part of split string
			tokens[1] = strtok(NULL, delim);// Get second part of split string

			if ((tokens[0] != NULL) && (tokens[1] != NULL)) {// If there is a name/value that is NULL
				if (!(strcmp(" ", tokens[0]) == 0 || strcmp(" ", tokens[1]) == 0)) {// If there is a blank name/value

					strcpy(name, tokens[0]);// Copy first part of string as name
					strcpy(value, tokens[1]);// Copy second part of string as value

					if (INTENT_FLAG == 1) {// If the knowledge is under the [what] intent, append under what_intent node
						EntityNode* head = EntityCreate_node((char*)name, value);
						if (what_intent->next == NULL) {
							what_intent->next = head;
						}
						else {
							Entity_insert_at_tail(what_intent->next, head);
						}
						linecount += 1;
					}
					else if (INTENT_FLAG == 2) {// If the knowledge is under the [where] intent, append under where_intent node
						EntityNode* head = EntityCreate_node((char*)name, value);
						if (where_intent->next == NULL) {
							where_intent->next = head;
						}
						else {
							Entity_insert_at_tail(where_intent->next, head);
						}
						linecount += 1;
					}
					else if (INTENT_FLAG == 3) {// If the knowledge is under the [who] intent, append under who_intent node
						EntityNode* head = EntityCreate_node((char*)name, value);
						if (who_intent->next == NULL) {
							who_intent->next = head;
						}
						else {
							Entity_insert_at_tail(who_intent->next, head);
						}
						linecount += 1;
					}
				}
				else {
					return -1;// Return -1 (num_of_lines in chatbot.c)
				}
			}
			else {
				return -1;// Return -1 (num_of_lines in chatbot.c)
			}
		}
	}
    return linecount;
}


/*
 * Reset the knowledge base, removing all know entities from all intents.
 */
void knowledge_reset() {

	if (where_intent != NULL) {
		if (where_intent->next != NULL) {
			EntityNode *head = where_intent->next;
			EntityNode *temp = head;
			while (temp != NULL) {
				temp = temp->next;
				free(head->entityName);
				free(head->answers);
				free(head);
				head = temp;

			}
			where_intent->next = NULL;
		}

	}
	/* Checks if user has asked any what questions and frees all the questions and answers */
	if (what_intent != NULL) {
		if (what_intent->next != NULL) {
			EntityNode *head = what_intent->next;
			EntityNode *temp = head;
			while (head != NULL) {
				temp = temp->next;
				free(head->entityName);
				free(head->answers);
				free(head);
				head = temp;
			}
			what_intent->next = NULL;
		}

	}
	/* Checks if user has asked any who questions and frees all the questions and answers */
	if (who_intent != NULL) {
		if (who_intent->next != NULL) {
			EntityNode *head = who_intent->next;
			EntityNode *temp = head;
			while (temp != NULL) {
				temp = temp->next;
				free(head->entityName);
				free(head->answers);
				free(head);
				head = temp;
			}
			who_intent->next = NULL;
		}

	}

}


/*
 * Write the knowledge base to a file.
 *
 * Input:
 *   f - the file
 */
void knowledge_write(FILE *f) {

	// What Intent List
	IntentNode *intent1 = what_intent;
	fprintf(f, "[%s]\n", intent1->intentName);

	EntityNode *entity1 = what_intent->next;
	while (entity1 != NULL) {
		fprintf(f, entity1->entityName);
		fprintf(f, "=");
		fprintf(f, entity1->answers);
		fprintf(f, "\n");
		entity1 = entity1->next;
	}
	fprintf(f, "\n");

	// Where Intent List
	IntentNode *intent2 = where_intent;
	fprintf(f, "[%s]\n", intent2->intentName);

	EntityNode *entity2 = where_intent->next;
	while (entity2 != NULL) {
		fprintf(f, entity2->entityName);
		fprintf(f, "=");
		fprintf(f, entity2->answers);
		fprintf(f, "\n");
		entity2 = entity2->next;
	}
	fprintf(f, "\n");

	// Who Intent List
	IntentNode *intent3 = who_intent;
	fprintf(f, "[%s]\n", intent3->intentName);

	EntityNode *entity3 = who_intent->next;
	while (entity3 != NULL) {
		fprintf(f, entity3->entityName);
		fprintf(f, "=");
		fprintf(f, entity3->answers);
		fprintf(f, "\n");
		entity3 = entity3->next;
	}
	fprintf(f, "\n");
}


/*
 * Creation of global intent nodes
 *
 * Returns:
 *	NULL
 */
void init_intentnodes() {
    //init of who intent
    who_intent = (IntentNode *) malloc(sizeof(IntentNode));
    if (who_intent == NULL) { //if memory not enough
        printf("Memory is full.");
        exit(1);
    }
    who_intent->intentName = calloc(4, sizeof(char)); //got to malloc the string pointer first
    strncpy(who_intent->intentName, "who", sizeof(char) * 4);
    who_intent->next = NULL;

    //init of what intent
    what_intent = (IntentNode *) malloc(sizeof(IntentNode));
    if (what_intent == NULL) { //if memory not enough
        printf("Memory is full.");
        exit(1);
    }
    what_intent->intentName = calloc(5, sizeof(char)); //got to malloc the string pointer first
    strncpy(what_intent->intentName, "what", sizeof(char) * 5);
    what_intent->next = NULL;

    //init of where intent
    where_intent = (IntentNode *) malloc(sizeof(IntentNode));
    if (where_intent == NULL) { //if memory not enough
        printf("Memory is full.");
        exit(1);
    }
    where_intent->intentName = calloc(6, sizeof(char)); //got to malloc the string pointer first
    strncpy(where_intent->intentName, "where", sizeof(char) * 6);
    where_intent->next = NULL;

}


/*
 * EntityNode search for entity name
 *
 * Returns:
 *	EntityNode
 */
EntityNode *Entitysearch_list(EntityNode *head, char *target) {
    EntityNode *temp = head;
    while (temp != NULL) { //while head not null
		if (temp->entityName != NULL) {
			if (compare_token(temp->entityName, target) != 0) { //while the value of the not-null temp is not the same
				temp = temp->next; //iterate through linked list
			}
			else {
				break; // break the loop if match
			}
		}
    }

//
    return temp;
}

EntityNode *EntityCreate_node(char *entity, char *ans) {
    EntityNode *new_node = (EntityNode *) malloc(sizeof(EntityNode));

    if (new_node != NULL) {
        new_node->entityName = calloc(strlen(entity) + 1, sizeof(char));
        new_node->answers = calloc(strlen(ans) + 1, sizeof(char));

        strncpy(new_node->entityName, entity, sizeof(char) * strlen(entity) + 1);
        strncpy(new_node->answers, ans, sizeof(char) * strlen(ans) + 1);
        new_node->next = NULL;
    }
    return new_node;
}

EntityNode *Entity_insert_at_tail(EntityNode *head, EntityNode *new_node) {
    if (head == NULL) {
        return new_node;
    }
    EntityNode *temp = head;


    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = new_node;
    return head;
}
