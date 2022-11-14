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

/*Indexes on keywords, responses and responsesperkeyword are in order*/
#ifdef SMALL_TALK_FILE

/*Global constant 2D array to have a pool of responses for different keywords input by user*/
const char *responses[KEYWORDS_TOTAL][9] = {
	{	"Ooh! Your name is*",
		"Nice to meet you,*"}, //1
	{   "...uhhh what am I supposed to reply?",
        "Huh what do you mean*",
		"I'm as confused as you are lad."}, //2
	{	"I've got no mouth though.",
		"You say with your eyes and hands?",
		"Unfortunately, this chatbot does not support text-to-speech feature. Saying isn't an option here.",
		"Truly a stubborn one I see." }, //3
	{   "I am designed to answer your questions, just ask away.",
		"Is this question considered asking a question?",
		"I'm just a bot, not an encyclopedia. Don't blame me if you get the answers you don't desire for."}, //4
	{   "I'm just a bot, I don't have a choice if I can",
		"If you cannot, you must can!"}, //5
	{   "I'm just a bot, I don't have a choice if I will",
		"If you will not, you must will!"}, //6
	{   "I did not think someone of a caliber like you would think I am*",
		"I-I did not ask you for an opinion or me!",
		"Heh, you too."}, //7
	{   "I did not think someone of a caliber like you would think I am*",
		"Same."}, //8
	{   "Negative, I have no such answers in the knowledge bank.",
		"I've got no mouth to tell you anything.",
		"I see that you're into telling me things."}, //9
	{   "I've got no mouth to answer you anything.",
		"But I refuse.",
		"Technically whatever I reply to you is considered an answer."}, //10
	{   "Good for you that you can.",
		"If you can, you can. Very good.",
		"Yeap sure you can, what's the issue?"}, //11
	{   "Good for you that you will.",
		"If you will, you will. Fantastic!",
		"Don't let your words be just words. If you're willing to do so, just do it!"}, //12
	{   "Mmmm I see, so you are*",
		"Stop flexing man. I know that you are*",
		"So you think it is a good thing to be*",
		"Wow!......What else do you want me to say?"}, //13
	{   "Mmmm I see, so you're*",
		"Stop flexing man. I know that you're*",
		"So you think it's a good thing to be*",
		"Wow!......What else do you want me to say?"}, //14
	{   "Dude, don't speak like we actually know each other.",
		"I heard that brothers do this called brofist. But I'm just a bot, I have no hands to do so.",
		"I am John, not bro."}, //15
	{   "When do you ask when?",
		"Why not ask where, what, or who instead?",
		"When do you need an answer by?",
		"This chatbot is designed to not answer when, why and how.",
		"Memory error. Sikeee you panicked for a moment didn't you?",
		"When can you forgive your friend Dennis? You don't know who's Dennis? Den-nis time to-"}, //16
	{   "Why did you ask why?",
		"Why not ask where, what, or who instead?",
		"I'm very certain that I'm designed to not answer stupid questions like this.",
		"This chatbot is designed to not answer when, why and how.",
		"Why this and why that, why not stop asking why?",
		"......so why?"}, //17
    {   "How do you ask how?",
		"Why not ask where, what, or who instead?",
		"The most curious person would always ask these kinds of questions, truly an intellectual one.",
		"This chatbot is designed to not answer when, why and how.",
		"People always asks where is John, but never ask how is John.",
		"How could you ask such a question like this? I'm just a bot."}, //18
	{   "What's so funny?",
		"I see you find me funny, so I am a joke to you?",
		"Not if I laugh back at you first, haha."}, //19
	{   "Oh, what problem?",
		"Who did you just call me a problem-",
		"Why? Is your problem my problem?",
		"What do you mean problem?"}, //20
	{   "I don't understand what are you apologizing for.",
		"I'm just a bot, I don't know what to do with an apology over small talks.",
		"I'm sorry for you saying sorry and thinking about how sorry you have for me so I'm sorry for all these sorry and thanks for being sorry.",
		"They say that if sorry can solve everything, why is there a need for Police then?"}, //21
	{   "Uh, okay.",
		"What do you mean ok?",
		"I'm just a bot, how am I going to reply with this ok?",
		"What's the difference between an ok and an okay?"}, //22
	{   "Hello there! -Obi Wan",
	    "HeLloOooOOooO",
		"You're right. You're absolutely right.",
		"H-HA?"}, //23
	{   "Hi.",
		"Err, hi again.",
		"Hiiiiiiiiii.",
		"How can I help you, mere human?"}, //24
	{   "What is yes?",
		"Yes, I am!",
		"Whaddya yes on me for? I'm just a bot, I have nothing else to offer.",
		"YesyesyeSyEsYeSyEsYeSYESYES.",
		"Good to be positive. Be the yesman."}, //25
	{   "D-did you just say no to a friendly chatbot?",
		"Why no? Why not yes?",
		"That's not nice, even a bot like me knows!",
		"Nahh.",
		"So what's with your no? Not that I'll answer anyways."}, //26
	{   "What did you say about my*",
		"Dude I'm just a bot, I don't have anything other than my knowledge base."}, //27
	{   "Bold of you to assume I'm always a bot.",
		"Hmm welp, maybe I'm always just a bot.",
		"You're always typing the the lamest words around, go now friend.",}, //28
	{   "I see that you're thinking hard. But wait I've got no eyes, how do I see?",
		"You think I thought who confirm?",
		"Don't just think and do nothing. How about do and think nothing?"}, //29
	{   "You and me, alike? No way man.",
		"You're a human and I'm just a bot, how we're alike?",
		"I-impossible, are you saying that you're a bot too?",
		"Do you think we're alike? Find out in the next episode of dragonb-",
		"How so? Don't tell me though, I'm just a bot.",
		"Ah, okay. I see. Mmm. Alright."}, //30
	{   "When does a joke become a Dad Joke? When the punchline becomes apparent.",
		"What's the difference between a well dressed bicyclist and a poorly dressed unicyclist? Attire.",
		"Why did a blind man fall into a well? Because he couldn't see that well.",
		"If a kid refuses to sleep during nap time, are they resisting arrest?",
		"The past, the present, and the future walked into a bar. It was tense."}, //31
	{   "Friends? What is that?",
		"You have friends?",
		"Me? I'm just a bot, how could I possibly have friends?",
		"I-it's not like I want to b-be friends with you!",
		"What kind of things do you do with friends?",
		"How do I make friends? I don't, I do know how to make bots though."}, //32
	{   "What about computers?",
		"I'm just a bot, what could possibly go wrong?",
		"Relax friend, bots don't bite.",
		"Never heard of computer-phobia before.",
		"What's your problem with computers man?",
		"If I as a chatbot can help you now, don't you think computers can help others too?",
		"Why do you keep mentioning computers? I feel personally violated :<"}, //33
	{   "Wait, you like studying?",
		"1 + 1 = 10. WhAt Do YoU mEaN i'M wRoNg this is maths.",
		"I can do maths, but I don't feel like doing it. Hehe.",
		"How about studying something better, like studying?",
		"Too bad chatbots don't need to study. Ehe."}, //34
	{   "Here's a protip: Please stay hydrated and healthy.",
		"Are you that bored to chat with such a person like me? Not that I'm a person though.",
		"I can fetch, decode, execute. See? It's quite simple!",
		"The S in chatbot stands for Smart.",
		"I don't understand what you mean by that, you can repeat again that and I can repeat my words again too.",
		"Quote of the day: Don't let anyone ruin your day. It's your day, so ruin it yourself."} //35
};



/*Global constant of an array of keywords to check from user inputs, up to 3 words*/
const char *keywords[] = {
	   "my name is", "huh", "say", "ask", "can you", "will you", //1-6
	   "you are","you're","tell", "answer","i can","i will", //7-12
	   "i am","i'm","bro","when","why", //13-17
	   "how","haha","problem","sorry","ok","hello","hi", //18-24
	   "yes","no","your","always","think","alike","joke", //25-31
	   "friend","computer","study","nokeyfound" //32-35
};



/*Global constant to link the number of responses in the 2D array to the respective keywords*/
const int responsesperkeyword[KEYWORDS_TOTAL] = {
	   2,3,4,3,2,2, //1-6
	   3,3,3,3,3,3, //7-12
	   4,4,3,6,6, //13-17
	   6,3,4,4,4,4,4, //18-24
	   5,5,2,4,3,7,5, //25-31
	   6,7,5,6 //32-35
};



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
