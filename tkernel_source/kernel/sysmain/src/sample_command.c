/*
 *----------------------------------------------------------------------
 *    T2EX Software Package
 *
 *    Copyright 2012 by Ken Sakamura.
 *    This software is distributed under the latest version of T-License 2.x.
 *----------------------------------------------------------------------
 *
 *    Released by T-Engine Forum(http://www.t-engine.org/) at 2012/12/12.
 *    Modified by T-Engine Forum at 2014/07/31.
 *    Modified by TRON Forum(http://www.tron.org/) at 2015/06/04.
 *
 *----------------------------------------------------------------------
 *
 *    Modified by T.Yokobayashi since 2019/10/10.
 *
 *----------------------------------------------------------------------
 */
/*
 * This software package is available for use, modification, 
 * and redistribution in accordance with the terms of the attached 
 * T-License 2.x.
 * If you want to redistribute the source code, you need to attach 
 * the T-License 2.x document.
 * There's no obligation to publish the content, and no obligation 
 * to disclose it to the TRON Forum if you have modified the 
 * software package.
 * You can also distribute the modified source code. In this case, 
 * please register the modification to T-Kernel traceability service.
 * People can know the history of modifications by the service, 
 * and can be sure that the version you have inherited some 
 * modification of a particular version or not.
 *
 *    http://trace.tron.org/tk/?lang=en
 *    http://trace.tron.org/tk/?lang=ja
 *
 * As per the provisions of the T-License 2.x, TRON Forum ensures that 
 * the portion of the software that is copyrighted by Ken Sakamura or 
 * the TRON Forum does not infringe the copyrights of a third party.
 * However, it does not make any warranty other than this.
 * DISCLAIMER: TRON Forum and Ken Sakamura shall not be held
 * responsible for any consequences or damages caused directly or
 * indirectly by the use of this software package.
 *
 * The source codes in bsd_source.tar.gz in this software package are 
 * derived from NetBSD or OpenBSD and not covered under T-License 2.x.
 * They need to be changed or redistributed according to the 
 * representation of each source header.
 */

/*
 *	@(#)command.c
 *
 */

#include <basic.h>
#include <tk/tkernel.h>
#include <tm/tmonitor.h>
///#include <t2ex/datetime.h>
///#include <t2ex/fs.h>
///#include <t2ex/load.h>
///#include <device/clk.h>

#include <libstr.h>
#define	strlen	STRLEN
#define	strcmp	STRCMP
#define	strtol	STRTOUL


#ifdef	USE_T2EX_FS
#define	P		printf
#else
#define	P		tm_printf
#endif

#define	N_ARGS		16

/*
	ref command
*/
#include "ref_command.c"


/*
	Initialize calendar date
*/
EXPORT	void	init_calendar_date(void)
{
	/* dummy */
	
	return;
}


/*
	test command
*/
LOCAL	void	cmd_test(INT ac, B *av[])
{
	INT i;

	P("ac = %d\n", ac);
	for (i=0; i<ac; i++) {
		P("av[%d]=\"%s\"\n", i, av[i]);
	}
	
	return;
}

/*
	call command
*/
LOCAL	void	cmd_call(INT ac, B *av[])
{
	FP	fnc;
	W	p1, p2, p3;

	if (ac < 2) return;

	fnc = (FP)strtol(av[1], NULL, 0);
	p1 = (ac >= 3) ? strtol(av[2], NULL, 0) : 0;
	p2 = (ac >= 4) ? strtol(av[3], NULL, 0) : 0;
	p3 = (ac >= 5) ? strtol(av[4], NULL, 0) : 0;

	(*fnc)(p1, p2, p3);
}

/*
	setup parameters
*/
LOCAL	INT	setup_param(B *bp, B **av)
{
	INT	ac;

	for (ac = 0; ac < N_ARGS; ac++) {
		while (*((UB*)bp) <= ' ' && *bp != '\0') bp++;
		if (*bp == '\0') break;
		av[ac] = bp;
		while (*((UB*)bp) > ' ') bp++;
		if (*bp != '\0') {
			*bp++ = '\0';
		}
	}
	av[ac] = NULL;
	return ac;
}

/*
	execute command
*/
EXPORT	INT	exec_cmd(B *cmd)
{
	INT	ac;
	B	*av[N_ARGS];

	ac = setup_param(cmd, av);
	if (ac < 1) return 0;

	if (strcmp(av[0], "test") == 0) {
		cmd_test(ac, av);
	} else if (strcmp(av[0], "ref") == 0) {
		cmd_ref(ac, av);
	} else if (strcmp(av[0], "call") == 0) {
		cmd_call(ac, av);
	} else if (av[0][0] == '?') {			/* strncmp "?" */
		P("test     [arg] ...\n");
		P("ref      [item]\n");
		P("call     addr [p1 p2 p3]\n");
	} else {
		return 0;
	}
	return 1;
}


/*----------------------------------------------------------------------
#|History of "sample_command.c"
#|-----------------------------
#|* 2019/10/10	Modified from T2EX "command.c" source by T.Yokobayashi.
#|
*/
