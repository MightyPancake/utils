/*

        Ansii ESCape

  Collection of macros for ANSII escape codes for use in terminal programs
  ie. colors, blinking, erasing etc.

*/

#ifndef UTILS_H_AESC_H
#define UTILS_H_AESC_H

#if defined(UTILS_H_ALL) || defined(UTILS_H_AESC) //Avoid defining if module was turned off
//Define types here
#ifndef aesc_printf
  #include <stdio.h>
  #define aesc_printf(FMT, ...) printf(FMT, ##__VAR_ARGS__)
#endif
#define aesc_do(C) aesc_printf(C)

#define aesc_seq(S) "\x1B"S
#define aesc_style(S) aesc_seq("["S"m")

// Colors
#define aesc_reset aesc_style("0")

#define aesc_black aesc_style("30")
#define aesc_red aesc_style("31")
#define aesc_green aesc_style("32")
#define aesc_yellow aesc_style("33")
#define aesc_blue aesc_style("34")
#define aesc_magenta aesc_style("35")
#define aesc_cyan aesc_style("36")
#define aesc_white aesc_style("37")
#define aesc_default aesc_style("39")

#define aesc_fg_color(V) aesc_seq("[38;5;"#V"m")
#define A_FC(V) aesc_fg_color(V)
const char* aesc_colors[] = {
  A_FC(0), A_FC(1), A_FC(2), A_FC(3), A_FC(4), A_FC(5), A_FC(6), A_FC(7), A_FC(8), A_FC(9),
  A_FC(10), A_FC(11), A_FC(12), A_FC(13), A_FC(14), A_FC(15), A_FC(16), A_FC(17), A_FC(18), A_FC(19),
  A_FC(20), A_FC(21), A_FC(22), A_FC(23), A_FC(24), A_FC(25), A_FC(26), A_FC(27), A_FC(28), A_FC(29),
  A_FC(30), A_FC(31), A_FC(32), A_FC(33), A_FC(34), A_FC(35), A_FC(36), A_FC(37), A_FC(38), A_FC(39),
  A_FC(40), A_FC(41), A_FC(42), A_FC(43), A_FC(44), A_FC(45), A_FC(46), A_FC(47), A_FC(48), A_FC(49),
  A_FC(50), A_FC(51), A_FC(52), A_FC(53), A_FC(54), A_FC(55), A_FC(56), A_FC(57), A_FC(58), A_FC(59),
  A_FC(60), A_FC(61), A_FC(62), A_FC(63), A_FC(64), A_FC(65), A_FC(66), A_FC(67), A_FC(68), A_FC(69),
  A_FC(70), A_FC(71), A_FC(72), A_FC(73), A_FC(74), A_FC(75), A_FC(76), A_FC(77), A_FC(78), A_FC(79),
  A_FC(80), A_FC(81), A_FC(82), A_FC(83), A_FC(84), A_FC(85), A_FC(86), A_FC(87), A_FC(88), A_FC(89),
  A_FC(90), A_FC(91), A_FC(92), A_FC(93), A_FC(94), A_FC(95), A_FC(96), A_FC(97), A_FC(98), A_FC(99),
  A_FC(100), A_FC(101), A_FC(102), A_FC(103), A_FC(104), A_FC(105), A_FC(106), A_FC(107), A_FC(108), A_FC(109),
  A_FC(110), A_FC(111), A_FC(112), A_FC(113), A_FC(114), A_FC(115), A_FC(116), A_FC(117), A_FC(118), A_FC(119),
  A_FC(120), A_FC(121), A_FC(122), A_FC(123), A_FC(124), A_FC(125), A_FC(126), A_FC(127), A_FC(128), A_FC(129),
  A_FC(130), A_FC(131), A_FC(132), A_FC(133), A_FC(134), A_FC(135), A_FC(136), A_FC(137), A_FC(138), A_FC(139),
  A_FC(140), A_FC(141), A_FC(142), A_FC(143), A_FC(144), A_FC(145), A_FC(146), A_FC(147), A_FC(148), A_FC(149),
  A_FC(150), A_FC(151), A_FC(152), A_FC(153), A_FC(154), A_FC(155), A_FC(156), A_FC(157), A_FC(158), A_FC(159),
  A_FC(160), A_FC(161), A_FC(162), A_FC(163), A_FC(164), A_FC(165), A_FC(166), A_FC(167), A_FC(168), A_FC(169),
  A_FC(170), A_FC(171), A_FC(172), A_FC(173), A_FC(174), A_FC(175), A_FC(176), A_FC(177), A_FC(178), A_FC(179),
  A_FC(180), A_FC(181), A_FC(182), A_FC(183), A_FC(184), A_FC(185), A_FC(186), A_FC(187), A_FC(188), A_FC(189),
  A_FC(190), A_FC(191), A_FC(192), A_FC(193), A_FC(194), A_FC(195), A_FC(196), A_FC(197), A_FC(198), A_FC(199),
  A_FC(200), A_FC(201), A_FC(202), A_FC(203), A_FC(204), A_FC(205), A_FC(206), A_FC(207), A_FC(208), A_FC(209),
  A_FC(210), A_FC(211), A_FC(212), A_FC(213), A_FC(214), A_FC(215), A_FC(216), A_FC(217), A_FC(218), A_FC(219),
  A_FC(220), A_FC(221), A_FC(222), A_FC(223), A_FC(224), A_FC(225), A_FC(226), A_FC(227), A_FC(228), A_FC(229),
  A_FC(230), A_FC(231), A_FC(232), A_FC(233), A_FC(234), A_FC(235), A_FC(236), A_FC(237), A_FC(238), A_FC(239),
  A_FC(240), A_FC(241), A_FC(242), A_FC(243), A_FC(244), A_FC(245), A_FC(246), A_FC(247), A_FC(248), A_FC(249),
  A_FC(250), A_FC(251), A_FC(252), A_FC(253), A_FC(254), A_FC(255), A_FC(256), A_FC(257), A_FC(258), A_FC(259)
};

char* aesc_hue[] = {A_FC(196), A_FC(202), A_FC(208), A_FC(214), A_FC(220), A_FC(226), A_FC(190), A_FC(154), A_FC(118), A_FC(82), A_FC(46), A_FC(47), A_FC(48), A_FC(49), A_FC(50), A_FC(51), A_FC(45), A_FC(39), A_FC(33), A_FC(27), A_FC(21), A_FC(57), A_FC(93), A_FC(129), A_FC(165), A_FC(201), A_FC(200), A_FC(199), A_FC(198), A_FC(197)};
#define aesc_hue_len (sizeof(aesc_hue)/sizeof(aesc_hue[0]))

#undef A_FC

//Cursor
#define aesc_home aesc_seq("[H")
#define aesc_mv(X, Y) aesc_seq("[" #X ";" #Y "f")
#define aesc_up(V) aesc_seq("[" #V "A")
#define aesc_down(V) aesc_seq("[" #V "B")
#define aesc_right(V) aesc_seq("[" #V "C")
#define aesc_left(V) aesc_seq("[" #V "D")

//Erase
#define aesc_clear aesc_seq("[J")
#define aesc_erase aesc_seq("[K")

//Map
#define aesc_map(I, S) aesc_seq("[" I ";" S ";p")

//end of types/macros
#if defined(UTILS_H_IMPLEMENTATION) || defined(UTILS_H_AESC_IMPLEMENTATION) //Implementation part only gets compiled once
//Declare variables here

//end of variables
#endif //UTILS_H_AESC_IMPLEMENTATION

#endif //UTILS_H_ALL || UTILS_H_AESC

#endif //UTILS_H_AESC_H
