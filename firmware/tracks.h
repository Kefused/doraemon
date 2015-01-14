#ifndef _COMMON_TRACKS_H
#define _COMMON_TRACKS_H

/*
Tracks definition
 */
#define N_TRACKS 8

#ifdef TRACKS_CN

	#define TRACK_0_LENGHT	4389
	#define TRACK_0_PAGE	0
	#define TRACK_0_OFFSET	0

	#define TRACK_1_LENGHT	17926
	#define TRACK_1_PAGE	8
	#define TRACK_1_OFFSET	165

	#define TRACK_2_LENGHT	25615
	#define TRACK_2_PAGE	42
	#define TRACK_2_OFFSET	139

	#define TRACK_3_LENGHT	13910
	#define TRACK_3_PAGE	90
	#define TRACK_3_OFFSET	410

	#define TRACK_4_LENGHT	28422
	#define TRACK_4_PAGE	117
	#define TRACK_4_OFFSET	64

	#define TRACK_5_LENGHT	30558
	#define TRACK_5_PAGE	170
	#define TRACK_5_OFFSET	502

	#define TRACK_6_LENGHT	23821
	#define TRACK_6_PAGE	228
	#define TRACK_6_OFFSET	436

	#define TRACK_7_LENGHT	18812
	#define TRACK_7_PAGE	273
	#define TRACK_7_OFFSET	497


#elif TRACKS_FR

	#define TRACK_0_LENGHT	4389
	#define TRACK_0_PAGE	0
	#define TRACK_0_OFFSET	0

	#define TRACK_1_LENGHT	20800
	#define TRACK_1_PAGE	352
	#define TRACK_1_OFFSET	313

	#define TRACK_2_LENGHT	32250
	#define TRACK_2_PAGE	49
	#define TRACK_2_OFFSET	114

	#define TRACK_3_LENGHT	21833
	#define TRACK_3_PAGE	110
	#define TRACK_3_OFFSET	156

	#define TRACK_4_LENGHT	19350
	#define TRACK_4_PAGE	151
	#define TRACK_4_OFFSET	341

	#define TRACK_5_LENGHT	53775
	#define TRACK_5_PAGE	188
	#define TRACK_5_OFFSET	155

	#define TRACK_6_LENGHT	32975
	#define TRACK_6_PAGE	290
	#define TRACK_6_OFFSET	74

	#define TRACK_7_LENGHT	21597
	#define TRACK_7_PAGE	8
	#define TRACK_7_OFFSET	165

#else

	#error "Unknown tracks type. Please run with TRACKS_TYPE=CN|FR"

#endif

#endif /* !_COMMON_TRACKS_H*/
