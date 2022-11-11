/*
 * INF1002 (C Language) Group Project, 2022-23 Trimester 1
 *
 * This file contains the definitions and function prototypes for all of
 * features of the INF1002 chatbot.
 */

#ifndef _CHAT1002_H
#define _CHAT1002_H

#include <stdio.h>

/*Max number of characters we expect in a line of input (including the terminating null)*/
#define MAX_INPUT    256

/*Max number of characters allowed in the name of an intent (including the terminating null)*/
#define MAX_INTENT   32

/*Max number of characters allowed in the name of an entity (including the terminating null)*/
#define MAX_ENTITY   64

/*Max number of characters allowed in a response (including the terminating null)*/
#define MAX_RESPONSE 256

/* return codes for knowledge_get() and knowledge_put() */
#define KB_OK        0
#define KB_NOTFOUND -1
#define KB_INVALID  -2
#define KB_NOMEM    -3

/* the variables required for smalltalk */
#define SWAP_TOTAL 14
#define KEYWORDS_TOTAL 35

/* data structures for intent and entities*/
typedef struct node_struct{
	char * entity_name;
	char * answer;
	struct node_struct *next;
} EntityNode;

typedef struct {
    char * intent_name;
    EntityNode *next;
} IntentNode;

#ifdef KNOWLEDGE_NODES
IntentNode * where_intent;
IntentNode * what_intent;
IntentNode * who_intent;
#endif

/*Indexes on keywords, responses and responsesperkeyword needs to be in order*/
/*Constant global variables to trigger small talk*/
#ifdef SMALL_TALK_FILE
const char *keywords[] = {
	   "why don't you", "why can't i", "my name is", "can you","can i","you are", //1-6
	   "you're","i don't","i feel", "are you","i can't","i want", //7-12
	   "i am","i'm","you","how","when", //13-17
	   "why","name","cause","sorry","dream","hello","hi", //18-24
	   "maybe","no","your","always","think","alike","yes", //25-31
	   "friend","computer","cars","nokeyfound" //32-35
	   /*
	   "I am","I'm","You","How","When", //13-17 to 1-5
	   "Maybe","No","Your","Always","Think","Alike","Yes", //25-31 to 6-12
	   "You're","I don't","I feel", "Are you","I can't","I want", //7-12 to 13-18
	   "Friend","Computer","Cars","Nokeyfound", //32-35 to 19-22
	   "Why don't you", "Why can't I", "My name is", "Can you","Can I","You are", //1-6 to 23-28
	   "Why","Name","Cause","Sorry","Dream","Hello","Hi", //18-24 to 29-35
	   */
};





/*
//backup
const char *keywords[] = {
	   "why don't you", "why can't i", "my name is", "can you","can i","you are", //1-6
	   "you're","i don't","i feel", "are you","i can't","i want", //7-12
	   "i am","i'm","you","how","when", //13-17
	   "why","name","cause","sorry","dream","hello","hi", //18-24
	   "maybe","no","your","always","think","alike","yes", //25-31
	   "friend","computer","cars","nokeyfound" //32-35
};
*/




const char *responses[KEYWORDS_TOTAL][9] = {
    {   "did you come to me because you are*",
		"how long have you been*",
		"do you believe it is normal to be*",
		"do you enjoy being*"}, //13
	{   "did you come to me because you are*",
		"how long have you been*",
		"do you believe it is normal to be*",
		"do you enjoy being*"}, //14
	{   "we were discussing you-- not me.",
		"oh, i*",
		"you're not really talking about me, are you?"}, //15
	{   "why do you ask?",
		"does that question interest you?",
		"what answer would please you the most?",
		"what do you think?",
		"are such questions on your mind often?",
		"what is it that you really want to know?",
		"have you asked anyone else?",
		"have you asked such questions before?",
		"what else comes to mind when you ask that?"}, //16
	{   "why do you ask?",
		"does that question interest you?",
		"what answer would please you the most?",
		"what do you think?",
		"are such questions on your mind often?",
		"what is it that you really want to know?",
		"have you asked anyone else?",
		"have you asked such questions before?",
		"what else comes to mind when you ask that?"}, //17
		{   "you don't seem quite certain.",
		"why the uncertain tone?",
		"can't you be more positive?",
		"you aren't sure?",
		"don't you know?"}, //25
	{   "are you saying no just to be negative?",
		"you are being a bit negative.",
		"why not?",
		"are you sure?",
		"why no?"}, //26
	{   "why are you concerned about my*",
		"what about your own*"}, //27
	{   "can you think of a specific example?",
		"when?",
		"what are you thinking of?",
		"really, always?"}, //28
	{   "do you really think so?",
		"but you are not sure you*",
		"do you doubt you*"}, //29
	{   "in what way?",
		"what resemblance do you see?",
		"what does the similarity suggest to you?",
		"what other connections do you see?",
		"could there really be some connection?",
		"how?"}, //30
	{   "you seem quite positive.",
		"are you sure?",
		"i see.",
		"i understand."}, //31
		{   "what makes you think i am*",
		"does it please you to believe i am*",
		"perhaps you would like to be*",
		"do you sometimes wish you were*"}, //7
	{   "don't you really*",
		"why don't you*",
		"do you wish to be able to*",
		"does that trouble you?"}, //8
	{   "tell me more about such feelings.",
		"do you often feel*",
		"do you enjoy feeling*"}, //9
	{   "why are you interested in whether or not i am*",
		"would you prefer if i were not*",
		"perhaps in your fantasies i am*"}, //10
	{   "how do you know you can't*",
		"have you tried?",
		"perhaps you can now*"}, //11
	{   "what would it mean to you if you got*",
		"why do you want*",
		"suppose you soon got*",
		"what if you never got*",
		"i sometimes also want*"}, //12
		{   "why do you bring up the topic of friends?",
		"do your friends worry you?",
		"do your friends pick on you?",
		"are you sure you have any friends?",
		"do you impose on your friends?",
		"perhaps your love for friends worries you?"}, //32
	{   "do computers worry you?",
		"are you talking about me in particular?",
		"are you frightened by machines?",
		"why do you mention computers?",
		"what do you think machines have to do with your problem?",
		"don't you think computers can help people?",
		"what is it about machines that worries you?"}, //33
	{   "oh, do you like cars?",
		"my favorite car is a lamborgini countach. what is your favorite car?",
		"my favorite car company is ferrari.  what is yours?",
		"do you like porsches?",
		"do you like porsche turbo carreras?"}, //34
	{   "say, do you like to have fun?",
		"what does that suggest to you?",
		"i see.",
		"i'm not sure i understand you fully.",
		"can you elaborate on that?",
		"that is quite interesting."}, //35
	{	"Would you really believe I don't*",
		"Maybe I would*",
		"Would you want me to*"}, //1
	{   	"Do you think you should be able to*",
		"But why can't you*"}, //2
	{	"Hi*",
		"Heya, how are you doing*",
		"Dangs what a cool name you have*",
		"alright cool cool cool.. hi again then*" }, //3
	{   "don't you believe that i can*",
		"perhaps you would like to be able to*",
		"you want me to be able to*"}, //4
	{   "perhaps you don't want to*",
		"do you want to be able to*"}, //5
	{   "what makes you think i am*",
		"does it please you to believe i am*",
		"perhaps you would like to be*",
		"do you sometimes wish you were*"}, //6
	{   "why do you ask?",
		"does that question interest you?",
		"what answer would please you the most?",
		"what do you think?",
		"are such questions on your mind often?",
		"what is it that you really want to know?",
		"have you asked anyone else?",
		"have you asked such questions before?",
		"what else comes to mind when you ask that?"}, //18
	{   "names don't interest me.",
		"i don't care about names-- please go on."}, //19
	{   "is that the real reason?",
		"don't any other reasons come to mind?",
		"does that reason explain any thing else?",
		"what other reasons might there be?"}, //20
	{   "please don't apologize.",
		"apologies are not necessary.",
		"what feelings do you have when you apologize?",
		"don't be so defensive!"}, //21
	{   "what does that dream suggest to you?",
		"do you dream often?",
		"what persons appear in your dreams?",
		"are you disturbed by your dreams?"}, //22
	{   "Hi! I'm John! What's yours?",
		"that's cool dude! have a great day!",
		"John here! What's your name?"}, //23
	{   "hi! I'm John! What's yours?",
		"that's cool dude! have a great day!",
		"John here! What's your name?"} //24


};









/*
//backup
const char *responses[KEYWORDS_TOTAL][9] = {
	{	"Would you really believe I don't*",
		"Maybe I would*",
		"Would you want me to*"}, //1
	{   	"Do you think you should be able to*",
		"But why can't you*"}, //2
	{	"Hi*",
		"Heya, how are you doing*",
		"Dangs what a cool name you have*",
		"alright cool cool cool.. hi again then*" }, //3
	{   "don't you believe that i can*",
		"perhaps you would like to be able to*",
		"you want me to be able to*"}, //4
	{   "perhaps you don't want to*",
		"do you want to be able to*"}, //5
	{   "what makes you think i am*",
		"does it please you to believe i am*",
		"perhaps you would like to be*",
		"do you sometimes wish you were*"}, //6
	{   "what makes you think i am*",
		"does it please you to believe i am*",
		"perhaps you would like to be*",
		"do you sometimes wish you were*"}, //7
	{   "don't you really*",
		"why don't you*",
		"do you wish to be able to*",
		"does that trouble you?"}, //8
	{   "tell me more about such feelings.",
		"do you often feel*",
		"do you enjoy feeling*"}, //9
	{   "why are you interested in whether or not i am*",
		"would you prefer if i were not*",
		"perhaps in your fantasies i am*"}, //10
	{   "how do you know you can't*",
		"have you tried?",
		"perhaps you can now*"}, //11
	{   "what would it mean to you if you got*",
		"why do you want*",
		"suppose you soon got*",
		"what if you never got*",
		"i sometimes also want*"}, //12
	{   "did you come to me because you are*",
		"how long have you been*",
		"do you believe it is normal to be*",
		"do you enjoy being*"}, //13
	{   "did you come to me because you are*",
		"how long have you been*",
		"do you believe it is normal to be*",
		"do you enjoy being*"}, //14
	{   "we were discussing you-- not me.",
		"oh, i*",
		"you're not really talking about me, are you?"}, //15
	{   "why do you ask?",
		"does that question interest you?",
		"what answer would please you the most?",
		"what do you think?",
		"are such questions on your mind often?",
		"what is it that you really want to know?",
		"have you asked anyone else?",
		"have you asked such questions before?",
		"what else comes to mind when you ask that?"}, //16
	{   "why do you ask?",
		"does that question interest you?",
		"what answer would please you the most?",
		"what do you think?",
		"are such questions on your mind often?",
		"what is it that you really want to know?",
		"have you asked anyone else?",
		"have you asked such questions before?",
		"what else comes to mind when you ask that?"}, //17
	{   "why do you ask?",
		"does that question interest you?",
		"what answer would please you the most?",
		"what do you think?",
		"are such questions on your mind often?",
		"what is it that you really want to know?",
		"have you asked anyone else?",
		"have you asked such questions before?",
		"what else comes to mind when you ask that?"}, //18
	{   "names don't interest me.",
		"i don't care about names-- please go on."}, //19
	{   "is that the real reason?",
		"don't any other reasons come to mind?",
		"does that reason explain any thing else?",
		"what other reasons might there be?"}, //20
	{   "please don't apologize.",
		"apologies are not necessary.",
		"what feelings do you have when you apologize?",
		"don't be so defensive!"}, //21
	{   "what does that dream suggest to you?",
		"do you dream often?",
		"what persons appear in your dreams?",
		"are you disturbed by your dreams?"}, //22
	{   "Hi! I'm John! What's yours?",
		"that's cool dude! have a great day!",
		"John here! What's your name?"}, //23
	{   "hi! I'm John! What's yours?",
		"that's cool dude! have a great day!",
		"John here! What's your name?"}, //24
	{   "you don't seem quite certain.",
		"why the uncertain tone?",
		"can't you be more positive?",
		"you aren't sure?",
		"don't you know?"}, //25
	{   "are you saying no just to be negative?",
		"you are being a bit negative.",
		"why not?",
		"are you sure?",
		"why no?"}, //26
	{   "why are you concerned about my*",
		"what about your own*"}, //27
	{   "can you think of a specific example?",
		"when?",
		"what are you thinking of?",
		"really, always?"}, //28
	{   "do you really think so?",
		"but you are not sure you*",
		"do you doubt you*"}, //29
	{   "in what way?",
		"what resemblance do you see?",
		"what does the similarity suggest to you?",
		"what other connections do you see?",
		"could there really be some connection?",
		"how?"}, //30
	{   "you seem quite positive.",
		"are you sure?",
		"i see.",
		"i understand."}, //31
	{   "why do you bring up the topic of friends?",
		"do your friends worry you?",
		"do your friends pick on you?",
		"are you sure you have any friends?",
		"do you impose on your friends?",
		"perhaps your love for friends worries you?"}, //32
	{   "do computers worry you?",
		"are you talking about me in particular?",
		"are you frightened by machines?",
		"why do you mention computers?",
		"what do you think machines have to do with your problem?",
		"don't you think computers can help people?",
		"what is it about machines that worries you?"}, //33
	{   "oh, do you like cars?",
		"my favorite car is a lamborgini countach. what is your favorite car?",
		"my favorite car company is ferrari.  what is yours?",
		"do you like porsches?",
		"do you like porsche turbo carreras?"}, //34
	{   "say, do you like to have fun?",
		"what does that suggest to you?",
		"i see.",
		"i'm not sure i understand you fully.",
		"can you elaborate on that?",
		"that is quite interesting."} //35
};
*/











const int responsesperkeyword[KEYWORDS_TOTAL] = {
	   4,4,3,9,9, //13-17 to 1-5
	   5,5,2,4,3,7,3, //25-31 to 6-12
	   4,4,3,3,3,5, //7-12 to 13-18
	   6,7,5,6, //32-35 to 19-22
	   3,2,4,3,2,4, //1-6 to 23-28
	   9,2,4,4,4,3,3, //18-24 to 29-35
};





/*
const int responsesperkeyword[KEYWORDS_TOTAL] = {
	   3,2,4,3,2,4, //1-6
	   4,4,3,3,3,5, //7-12
	   4,4,3,9,9, //13-17
	   9,2,4,4,4,3,3, //18-24
	   5,5,2,4,3,7,3, //25-31
	   6,7,5,6 //32-35
};
*/






const char *swaps[SWAP_TOTAL][2] = {
	{"are","am"},
	{"were", "was"},
	{"you","i"},
	{"your", "my"},
	{"ive", "you've"},
	{"im", "you're"},
	{"you", "me"},
	{"me", "you"},
	{"am","are"},
	{"was", "were"},
	{"i","you"},
	{"my", "your"},
	{"youve", "i've"},
	{"youre", "i'm"}
};


int * replycount;
#endif



/* functions defined in chatbot.c */
const char *chatbot_botname();
const char *chatbot_username();
int chatbot_main(int inc, char *inv[], char *response, int n);
int chatbot_is_exit(const char *intent);
int chatbot_do_exit(int inc, char *inv[], char *response, int n);
int chatbot_is_load(const char *intent);
int chatbot_do_load(int inc, char *inv[], char *response, int n);
int chatbot_is_question(const char *intent);
int chatbot_do_question(int inc, char *inv[], char *response, int n);
int chatbot_is_reset(const char *intent);
int chatbot_do_reset(int inc, char *inv[], char *response, int n);
int chatbot_is_save(const char *intent);
int chatbot_do_save(int inc, char *inv[], char *response, int n);
int chatbot_do_smalltalk(int inc, char *inv[], char *resonse, int n);
int * findpos(int inc, char ** temp_input);
void init_keywordcounters();


/* functions defined in main.c */
int compare_token(const char *token1, const char *token2);
void prompt_user(char *buf, int n, const char *format, ...);


/* functions defined in knowledge.c */
int knowledge_get(const char *intent, char *entity, char *response, int n);
int knowledge_put(const char *intent, const char *entity, const char *response,int n);
void knowledge_reset();
int knowledge_read(FILE *f);
void knowledge_write(FILE *f);
void init_intentnodes();
EntityNode *Entitysearch_list(EntityNode *head, char *target);
EntityNode *EntityCreate_node(char* entity, char* ans);
EntityNode *Entity_insert_at_tail(EntityNode *head, EntityNode *new_node);
#endif
