# INPlutus
A Cardano Plutus hacking package for learning. This is a work in progress.


SUMMARY

A Plutus hacking software collection aimed at building an understanding
without reliance on IOHK/IOG's software. (If you are reading this, this is
just the start of the project, and you want to come back when this message
will have changed, and change it will, I promise.)


MOTIVATION (and a personal perspective)

This is a product of frustration. I _love_ what IOHK/IOG have done with the
Cardano blockchain, and how they have structured their vision for an open
value-exchange and "decentralized finance" platform. However, their products
do not fit my personality. Consequently, I decided to go completely rogue
and put my hacker-from-the-90s hat on, and do things in a way that they can
be understood by me and be easily explained to others. In this vane attempt,
I am trying to break down Plutus, and build a software stack that can be
used _outside_ of IOHK/IOG's framework. If it further helps decentralization,
even better.


A REQUEST FOR HELP

Can somebody please get a hold of Titto Assini's "Flat.pdf" document?
He (https://github.com/tittoassini) is MIA and his site, where the Plutus
Specification document references point to the file, is down. (What a
fisasco... The single Plutus specification document I can find has no author,
and the references are to a non-responsive site. You sense my frustration..)


CONTENTS AND LOG-BOOK

IN 2021/11/19 (initial creation)
 - Added a Makefile, a driver (main.c), and the "inp.*" code.
 - Added a ubiquitous version of the "AlwaysSucced" Plutus script file.
 - The framework can read and parse a Plutus script "V1" in JSON format.
 - The non-intuitive step of turning "flat untyped Plutus" to a printable binary
   form is taken when the script file is read.

