A text-based learning robot.


I've been working on a chatbot on and off for about 11 years, and while I've made a lot of progress, there's a great deal of work left to do. I was thinking that if this was a group project, development would pick up speed considerably, plus it could be more fun to work on. I'd like see if there's any interest out there.

I wanted to make a chatbot that is better than the AIML types. Something that would pay attention to who it was talking to and try to learn from that person. It would not guess at an answer when it has no understanding of that was said. If it doesn't understand, it will explain why and ask for information in an attempt to understand. What it learns can be applied later in the conversation and with other users.

Note: There's more info in the wiki.

## About this program
* This is a text based robot that tries to get to know its users over a period of time
* It will try to make sense of every word in a sentence. It will never pretend to know its meaning. It will attempt to explain what it's having trouble with. The user may be able to explain new words that are new to it.
* Its database relies on a classification of basic knowledge
* It uses templates to interpret sentences
* Only certain types of words are allowed to fit in the templates
* It starts out with simple features and is expandable
* ID numbers are used identify specific members of a category, usually people could also be pets, buildings database entries start with a number sign followed by the id number* Will expect to know who it's talking to
* Will remember elements of conversations
* Will try to use people to expand it's knowledge
## Long term goals
* Will form opinions of the people it talks to
* Will initiate conversation if the user doesn't
* Will be thinking of various things when it's not in a conversation. This activity may have an effect on its mood, may cause it to arrive at some conclusions. It may be prompted to ask related questions. It can be asked "what are you thinking about".

## The database
It's a text file called general.txt. Information is stored as a list of key-value pairs, one pair per line. The key is a series of increasingly specific keywords separated by the ">" character. Any information that is gathered during user sessions gets added to the end of the file. Specific entities such as "ronald" or "my computer" are given ID numbers. 

There is a set of functions for easy access to it.
* db_check - checks to see if a word is in the database
* db_lookup - give it a key and it returns a value
* db_add_pair - adds an item to the database
* db_root_check - checks if a word belongs to the specified class(is a subset of) 
* db_get_id - looks up a persons first name and returns their ID number
* db_next_available_id - provides an unused id number to be used when adding a new person (or any other specific entity) to the database

## Limitations
* Only full sentences
* No pronouns, adjectives or adverbs
* No figures of speech
* No slang
* No compound sentences (example: "Hi, how are you")
* Ignores multiple meanings 

## Programming details
* Language: C
* Editor: Code::Blocks
* Compiler: GCC
* Platform: Raspberry Pi with Raspian

## What I need help with
* Clearer and more complete documentation
* Clearer code
* The various issues in the issue list
* Ideas in general

See "Issues" for a list of things that need to be worked on.
