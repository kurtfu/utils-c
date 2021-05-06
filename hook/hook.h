#ifndef HOOK_H
#define HOOK_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/*****************************************************************************/
/*  MACRO DEFINITIONS                                                        */
/*****************************************************************************/

#define HOOK_OK             0
#define HOOK_NULL_PTR      -1
#define HOOK_INVALID_HOOK  -2

/*****************************************************************************/
/*  DATA TYPES                                                               */
/*****************************************************************************/

struct subject
{
    struct hook* list;
};

/*****************************************************************************/
/*  PUBLIC FUNCTIONS                                                         */
/*****************************************************************************/

int hook_attach(struct subject* subj, void (*event)(void* args), void* args);
int hook_detach(struct subject* subj, void (*event)(void* args));
int hook_notify(struct subject* subj);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* HOOK_H */
