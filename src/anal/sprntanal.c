#include <gkstring.h>
#include "sprntanal.proto.h"


void sPrntAnalyses(char * res, gk_word *Gkword) {
  int nanals;
  nanals = totanal_of(Gkword);

  SortAnals(analysis_of(Gkword), nanals);
  sdump_all_anals(res, Gkword);
}


sGoodAnals(gk_word * Gkword, int lemmflag) {
  char curlem[MAXWORDSIZE];
  gk_analysis * anal;
  int goodanals = 0;
  int difflems = 0;
  int i;
	
  curlem[0] = 0;

  for(i=0; i<totanal_of(Gkword); i++) {
    anal = analysis_of(Gkword)+i;
    if( strcmp(curlem, lemma_of(anal) ) ) {
      difflems ++;
      strcpy(curlem, lemma_of(anal));
    }
    if( (strchr(lemma_of(anal),'-') == NULL ) ) {
      goodanals++;
    }
  }
  return(lemmflag ? difflems : goodanals );
}


void sdump_all_anals(char * res, gk_word *Gkword) {
  int i = 0;
  int nanals = totanal_of(Gkword);
  int goodanals = 0;
  char * r_anal;
  gk_analysis * anal;
	
  goodanals = sGoodAnals(Gkword,0);
  sprintf(res, "%s\n", rawword_of(Gkword));

  for(i=0; i<nanals; i++) {
    anal = analysis_of(Gkword)+i;

    if( !goodanals || (goodanals && (!strchr(lemma_of(anal),'-'))) ) {
        sDumpPerseusAnalysis(res, Gkword, anal);
    }
  }
  strcat(res, "\n");
}


/*int sCompAnals(const void*, const void*);*/

sSortAnals(gk_analysis *anal, int nanals) {
  qsort(anal, (long)nanals, (int)sizeof * anal, sCompAnals);
}

int sCompAnals(const void* anal1, const void* anal2) {
  return(strcmp(lemma_of((gk_analysis*)anal1), lemma_of((gk_analysis*)anal2)));
}


void sDumpPerseusAnalysis(char * res, gk_word *Gkword, gk_analysis *anal) {
  char tmp[LONGSTRING];
  char * form = "I";
  char workf[MAXWORDSIZE];
	
  if( Is_participle(anal )) {
      form = "P";
  }	else if( Is_nounform(anal) || Is_adjform(anal) ) {
      form = "N";
  }
  else if( Is_verbform(anal) ) {
      form = "V";
  } 

  if (strcmp(rawword_of(anal), workword_of(anal))) {
    
    strcpy(workf, workword_of(anal));
    if( strcmp(rawword_of(anal), workf))
      strcat(workf, ",");
    } else {
        sprintf(workf, "");
    }

  sprintf(tmp, "<NL>%s %s%s ", form, workf, lemma_of(anal));
  GregSprintGkFlags(anal, tmp, " ", " ", 1);
  strcat(tmp, "</NL>");

  strcat(res, tmp);
}

