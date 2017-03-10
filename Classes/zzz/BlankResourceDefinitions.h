#ifndef __RESOURCE_DEFINITIONS_H__
#define __RESOURCE_DEFINITIONS_H__

#include "cocos2d.h"

    // These resources are generally used throughout the app

const std::string FELTFONT = "fonts/Marker Felt.ttf";
const float TEXTSIZE = 1.0f/20; // This was chosen so that 3 lines of text fits into text boxes
const float VOLUMEMUSIC = 0.8f; // may not be used anymore..

const float TEMPO = 1.0f / 1.0f; // works inversely to control app speed: 1/10 == 10x faster
const float SCENETRANSITIONTIME = 2.0f*TEMPO; // times for screen wipes

    // These resources govern the launch screen

const float LAUNCHTRANSITIONTIME = 6.0f*TEMPO;
const std::string LAUNCHIMAGE = "res/blanks/blankBackground.png";

const char BCKMUSICINTRO[19] = "audio/ch3music.wav";
const char BCKMUSICMENU[19] = "audio/ch1music.wav";
const char BCKMUSICALMAMATER[19] = "audio/ch2music.wav";
const char BCKMUSICCH1[19] = "audio/ch1music.wav";
const char BCKMUSICCH2[19] = "audio/ch2music.wav";
const char BCKMUSICCH3[19] = "audio/ch3music.wav";
const char BCKMUSICCH4[19] = "audio/ch4music.wav";

const char CLICKSOUND[17] = "audio/chimes.wav";
const char KNOCKSOUND[17] = "audio/chimes.wav";

    //These resources determine the order of the credits

const std::string CONTACT = "res/blanks/blankBackground.png";
const std::string ABOUT1 = "res/blanks/blankBackground.png";
const std::string ABOUT2 = "res/blanks/blankBackground.png";
const std::string ABOUT3 = "res/blanks/blankBackground.png";
const std::string ABOUT4 = "res/blanks/blankBackground.png";
const std::string ABOUT5 = "res/blanks/blankBackground.png";

    //These resources are for the certificate and extra stuff

const std::string COMPLETEDPROTONU = "res/blanks/blankBackground.png";

    //These resources are for the main menu

const std::string BEGINSTORYIMAGE = "res/blanks/blankBackground.png";
const std::string BEGINSTORYBUTTON = "res/MainMenu/menu_begin.png";

const float MENUTRANSITIONTIME = 45.0F*TEMPO;

const std::string RESUMEON = "res/buttons/btn_resume_tap.png";
const std::string RESUMEOFF = "res/buttons/btn_resume_static.png";
const std::string ABOUTON = "res/buttons/btn_about_tap.png";
const std::string ABOUTOFF = "res/buttons/btn_about_static.png";

const std::string CH1ON = "res/chapterbuttons/1_chapter_active_01.png";
const std::string CH1OFF = "res/chapterbuttons/1_chapter_static_01.png";
const std::string CH2ON = "res/chapterbuttons/1_chapter_active_02.png";
const std::string CH2OFF = "res/chapterbuttons/1_chapter_static_02.png";
const std::string CH3ON = "res/chapterbuttons/1_chapter_active_03.png";
const std::string CH3OFF = "res/chapterbuttons/1_chapter_static_03.png";
const std::string CH4ON = "res/chapterbuttons/1_chapter_active_04.png";
const std::string CH4OFF = "res/chapterbuttons/1_chapter_static_04.png";
const std::string CH5ON = "res/chapterbuttons/1_chapter_active_05.png";
const std::string CH5OFF = "res/chapterbuttons/1_chapter_static_05.png";

    //These resource are for navigation of the chapters

const std::string FRAMEIMAGE = "res/frame nav/frame.png";
const std::string HOMEOFF = "res/frame nav/btn_home_static.png";
const std::string HOMEON = "res/frame nav/btn_home_tap.png";
const std::string VOLUMEOFF = "res/frame nav/btn_vol_on_static.png";
const std::string VOLUMEON = "res/frame nav/btn_vol_on_tap.png";
const std::string STARSOFF = "res/frame nav/btn_stars_static.png";
const std::string STARSON = "res/frame nav/btn_stars_tap.png";
const std::string NOTESOFF = "res/frame nav/btn_notes_static.png";
const std::string NOTESON = "res/frame nav/btn_notes_tap.png";

const std::string NAVLEFTOFF = "res/frame nav/btn_nav-left_static.png";
const std::string NAVLEFTON = "res/frame nav/btn_nav-left_tap.png";
const std::string NAVRIGHTOFF = "res/frame nav/btn_nav-right_static.png";
const std::string NAVRIGHTON = "res/frame nav/btn_nav-right_tap.png";

const std::string TEXTBOX = "res/frame nav/frame_text_box.png";
const std::string EXITBUTTON = "res/buttons/exit.png";

    //These resources are characters

const std::string JEFFERSONIMAGE = "res/Characters/3_jefferson.png"; //Jefferson_Arms_Up too big
const std::string JEFFERSONWAVEIMAGE = "res/Characters/1_jefferson_wave.png";
const std::string CHILDLIFESPECIALISTIMAGE = "res/Characters/1_child_life_specialist.png";
const std::string DOCIMAGE = "res/Characters/2_character_doc.png";
const std::string NURSE1IMAGE = "res/Characters/2_character_nurse1.png";
const std::string NURSE2IMAGE = "res/Characters/2_character_nurse2.png";
const std::string SOCIALWORKERIMAGE = "res/Characters/2_character_socialworker.png";
const std::string THERAPISTIMAGE = "res/Characters/2_character_therapist.png";
const std::string TAPTHESCREEN = "res/Chapter4/gantry_instructions.png";


    //These resources are for Chapter 1

const std::string BUILDINGIMAGE = "res/blanks/blankBackground.png";
const std::string LOBBYIMAGE = "res/blanks/blankBackground.png";

const std::string BUBBLENWIMAGE = "res/frame nav/1_bubble_homebtn.png";
const std::string BUBBLENEIMAGE = "res/frame nav/1_bubble_chaptersbtn.png";
const std::string BUBBLESWIMAGE = "res/frame nav/1_bubble_starbtn.png";
const std::string BUBBLESEIMAGE = "res/frame nav/1_bubble_notesbtn.png";

const char CH1AUDIOWEEEEEEEE[17] = "audio/chimes.wav";
const float CH1AUDIOTIMEWEEEEE = 4.18f*TEMPO;

const char CH1AUDIOHI[17] = "audio/chimes.wav";
const float CH1AUDIOTIMEHI = 11.05f*TEMPO;

const float EXPLAINFRAMEBUTTONSTIME = 3.5f*TEMPO;

const char CH1AUDIOGOINSIDE[17] = "audio/chimes.wav";
const char CH1AUDIOTIMEGOINSIDE = 5.07f*TEMPO;

const char CH1AUDIOTHISISTHELOBBY[17] = "audio/chimes.wav";
const char CH1AUDIOTIMETHISISTHELOBBY = 5.9f*TEMPO;

const char CH1AUDIOCHILDLIFEHI[17] = "audio/chimes.wav";
const char CH1AUDIOTIMECHILDLIFEHI = 5.41f*TEMPO;

const char CH1AUDIORADIATIONMEDICINE[17] = "audio/chimes.wav";
const char CH1AUDIOTIMERADIATIONMEDICINE = 19.32f*TEMPO;

    //These resources are for Chapter 2

const std::string HALLWAYIMAGE = "res/blanks/blankBackground.png";
const std::string EXAMROOMIMAGE = "res/blanks/blankBackground.png";
const std::string BLUEDOORCLOSED = "res/blanks/blankBackground.png";
const std::string BLUEDOOROPEN = "res/blanks/blankBackground.png";
const std::string GREENDOORCLOSED = "res/blanks/blankBackground.png";
const std::string GREENDOOROPEN = "res/blanks/blankBackground.png";
const std::string ORANGEDOORCLOSED = "res/blanks/blankBackground.png";
const std::string ORANGEDOOROPEN = "res/blanks/blankBackground.png";

const char CH2AUDIOMEETRADTHERAPIST[17] = "audio/chimes.wav";
const float CH2AUDIOTIMEMEETRADTHERAPIST = 6.01f*TEMPO;

const char CH2AUDIOTAP2[17] = "audio/chimes.wav";
const float CH2AUDIOTIMETAP2 = 2.27f*TEMPO;

const char CH2AUDIORADTHERAPIST[17] = "audio/chimes.wav";
const float CH2AUDIOTIMERADTHERAPIST = 10.48f*TEMPO;

const char CH2AUDIOHIGHTECH[17] = "audio/chimes.wav";
const float CH2AUDIOTIMEHIGHTECH = 3.37f*TEMPO;

const char CH2AUDIOMEETSOCIALWORKER[17] = "audio/chimes.wav";
const float CH2AUDIOTIMEMEETSOCIALWORKER = 6.24f*TEMPO;

const char CH2AUDIOSOCIALWORKER[17] = "audio/chimes.wav";
const float CH2AUDIOTIMESOCIALWORKER = 16.0f*TEMPO;

const char CH2AUDIOMEETNURSEDOCTOR[17] = "audio/chimes.wav";
const float CH2AUDIOTIMEMEETNURSEDOCTOR = 6.14f*TEMPO;

const char CH2AUDIORESTOFTEAM[17] = "audio/chimes.wav";
const float CH2AUDIOTIMERESTOFTEAM = 3.03f*TEMPO;

const char CH2AUDIONURSE[17] = "audio/chimes.wav";
const float CH2AUDIOTIMENURSE = 10.48f*TEMPO;

const char CH2AUDIODOCTOR[17] = "audio/chimes.wav";
const float CH2AUDIOTIMEDOCTOR = 13.92f*TEMPO;

const char CH2AUDIOSTAYSTILLGAME[17] = "audio/chimes.wav";
const float CH2AUDIOTIMESTAYSTILLGAME = 17.89f*TEMPO;

const char CH2AUDIOAGAINWIGGLE[17] = "audio/chimes.wav";
const float CH2AUDIOTIMEAGAINWIGGLE = 6.01f*TEMPO;

const char CH2AUDIOHARDERTOAIM[17] = "audio/chimes.wav";
const float CH2AUDIOTIMEHARDERTOAIM = 8.99f*TEMPO;

const char CH2AUDIOSOUNDSTRICKY[17] = "audio/chimes.wav";
const float CH2AUDIOTIMESOUNDSTRICKY = 11.18f*TEMPO;

    //These resources are for Chapter 3

const std::string CTROOMIMAGE = "res/blanks/blankBackground.png";

const std::string MAKEPILLOWIMAGE = "res/Chapter3/3_pillowbkg.png";
const std::string PILLOWGUMDROPIMAGE = "res/Chapter3/3_pillow_05.png";
const std::string PILLOWIMAGE = "res/Chapter3/3_pillow.png";
const std::string PILLOWDEFLATEDIMAGE = "res/Chapter3/3_pillowdeflated.png";
const std::string PILLOWHALFIMAGE = "res/Chapter3/3_pillowhalffull.png";
const std::string JEFFERSONOUTLINEIMAGE = "res/Chapter3/3_jeffersonOutline.png";


const std::string MAKEMASKIMAGE = "res/blanks/blankBackground.png";

const std::string MASKBEFOREIMAGE = "res/Chapter3/3_mask_step1active.png";
const std::string MASKOUTLINEIMAGE = "res/Chapter3/3_mask_outlinepng.png";
const std::string MASKJEFFERSONBEFOREIMAGE = "res/Chapter3/3_mask_step3active.png";
const std::string MASKJEFFERSONAFTERIMAGE = "res/Chapter3/3_mask_step3static.png";
const std::string MASKJEFFERSONAFTERNOSHADOWIMAGE = "res/Chapter3/3_mask_step3static_noshadow.png";

const std::string MASKWATERIMAGE = "res/Chapter3/3_mask_step2active.png";
const std::string MASKDROPLETSIMAGE = "res/Chapter3/3_mask_droplets.png";


const char CH3AUDIOWELCOMECT[17] = "audio/chimes.wav";
const float CH3AUDIOTIMEWELCOMECT = 10.4f*TEMPO;

const char CH3AUDIOBEANBAG[17] = "audio/chimes.wav";
const float CH3AUDIOTIMEBEANBAG = 11.0f*TEMPO;

const char CH3AUDIOPRACTICEPILLOW[17] = "audio/chimes.wav";
const float CH3AUDIOTIMEPRACTICEPILLOW = 4.52f*TEMPO;

const char CH3AUDIOPILLOW[17] = "audio/chimes.wav";
const float CH3AUDIOTIMEPILLOW = 14.92f*TEMPO;

const char CH3AUDIOGOACTVITIES[17] = "audio/chimes.wav";
const float CH3AUDIOTIMEGOACTIVITIES = 4.52f*TEMPO;

const char CH3AUDIOSPECIALPILLOW[17] = "audio/chimes.wav";
const float CH3AUDIOTIMESPECIALPILLOW = 13.01f*TEMPO;

const char CH3AUDIOMAKEMASK[17] = "audio/chimes.wav";
const float CH3AUDIOTIMEMAKEMASK = 4.52f*TEMPO;

const char CH3AUDIONOTMASK[17] = "audio/chimes.wav";
const float CH3AUDIOTIMENOTMASK = 3.03f*TEMPO;

const char CH3AUDIOWETNOODLE[17] = "audio/chimes.wav";
const float CH3AUDIOTIMEWETNOODLE = 9.25f*TEMPO;

const char CH3AUDIOWHILEWET[17] = "audio/chimes.wav";
const float CH3AUDIOTIMEWHILEWET = 7.76f*TEMPO;

const char CH3AUDIOYUMMY[17] = "audio/chimes.wav";
const float CH3AUDIOTIMEYUMMY = 4.99f*TEMPO;

const char CH3AUDIOSILLY[17] = "audio/chimes.wav";
const float CH3AUDIOTIMESILLY = 7.5f*TEMPO;

const char CH3AUDIOYUCKY[17] = "audio/chimes.wav";
const float CH3AUDIOTIMEYUCKY = 1.2f*TEMPO;

const char CH3AUDIOCATSCAN[17] = "audio/chimes.wav";
const float CH3AUDIOTIMECATSCAN = 7.5f*TEMPO;

const char CH3AUDIOCATSCAN2[17] = "audio/chimes.wav";
const float CH3AUDIOTIMECATSCAN2 = 1.31f*TEMPO;

const char CH3AUDIOFORPEOPLE[17] = "audio/chimes.wav";
const float CH3AUDIOTIMEFORPEOPLE = 4.52f*TEMPO;

const char CH3AUDIOSMILE[17] = "audio/chimes.wav";
const float CH3AUDIOTIMESMILE = 10.48f*TEMPO;

const char CH3AUDIOAFTERCT[17] = "audio/chimes.wav";
const float CH3AUDIOTIMEAFTERCT = 19.64f*TEMPO;

const std::string CALENDARBACKGROUNDIMAGE = "res/blanks/blankBackground.png";

const std::string CALENDARARTIMAGE = "res/Chapter3/calendar_Art.png";
const std::string CALENDARBEACHIMAGE = "res/Chapter3/calendar_Beach.png";
const std::string CALENDARCARIMAGE = "res/Chapter3/calendar_Car.png";

const std::string CALENDARFISHIMAGE = "res/Chapter3/calendar_Fish.png";
const std::string CALENDARFISHINGIMAGE = "res/Chapter3/calendar_Fishing.png";
const std::string CALENDARFLASKIMAGE = "res/Chapter3/calendar_Flask.png";

const std::string CALENDARFOOTBALLIMAGE = "res/Chapter3/calendar_Football.png";
const std::string CALENDARPROTONUIMAGE = "res/Chapter3/calendar_ProtonU.png";
const std::string CALENDARSOCCERIMAGE = "res/Chapter3/calendar_Soccer.png";

const std::string CALENDARSPACEIMAGE = "res/Chapter3/calendar_Space.png";
const std::string CALENDARZOOIMAGE = "res/Chapter3/calendar_Zoo.png";

    //These resources are for Chapter 4

const std::string GANTRYIMAGE = "res/blanks/blankBackground.png";

const std::string ARROWIMAGE = "res/blanks/blankBackground.png";

const std::string GANTRYINSTRUCTIONS = "res/Chapter4/gantry_instructions.png";
const std::string BARFOROBJECTS = "res/Chapter4/bar_for_objects.png";

const std::string CAMERALEFTIMAGE = "res/Chapter4/icon_camera-left_drag.png";
const std::string CAMERALEFTGHOSTIMAGE = "res/Chapter4/icon_camera-left_ghost.png";
const std::string CAMERARIGHTIMAGE = "res/Chapter4/icon_camera-right_drag.png";
const std::string CAMERARIGHTGHOSTIMAGE = "res/Chapter4/icon_camera-right_ghost.png";
const std::string SNOUTIMAGE = "res/Chapter4/icon_snout_drag.png";
const std::string SNOUTGHOSTIMAGE = "res/Chapter4/icon_snout_ghost.png";
const std::string SPEAKERIMAGE = "res/Chapter4/icon_speaker_drag.png";
const std::string SPEAKERGHOSTIMAGE = "res/Chapter4/icon_speakers_ghost.png";
const std::string TABLEIMAGE = "res/Chapter4/icon_table_drag.png";
const std::string TABLEGHOSTIMAGE = "res/Chapter4/icon_table_ghost.png";
const std::string XRAYIMAGE = "res/Chapter4/icon_xray_drag.png";
const std::string XRAYGHOSTIMAGE = "res/Chapter4/icon_xray_ghost.png";

const char CH4AUDIOTREATMENTHAPPENS[17] = "audio/chimes.wav";
const float CH4AUDIOTIMETREATMENTHAPPENS = 6.11f*TEMPO;

const char CH4AUDIOLETSLEARN[17] = "audio/chimes.wav";
const float CH4AUDIOTIMELETSLEARN = 6.01f*TEMPO;

const char CH4AUDIOSNOUT[17] = "audio/chimes.wav";
const float CH4AUDIOTIMESNOUT = 7.5f*TEMPO;

const char CH4AUDIOTABLE[17] = "audio/chimes.wav";
const float CH4AUDIOTIMETABLE = 10.48f*TEMPO;

const char CH4AUDIOXRAY[17] = "audio/chimes.wav";
const float CH4AUDIOTIMEXRAY = 4.52f*TEMPO;

const char CH4AUDIOCAMERAS[17] = "audio/chimes.wav";
const float CH4AUDIOTIMECAMERAS = 6.16f*TEMPO;

const char CH4AUDIOSOUND[17] = "audio/chimes.wav";
const float CH4AUDIOTIMESOUND = 7.5f*TEMPO;

const char CH4AUDIOSINGDANCE[17] = "audio/chimes.wav";
const float CH4AUDIOTIMESINGDANCE = 4.83f*TEMPO;

const char CH4AUDIOBEQUIET[17] = "audio/chimes.wav";
const float CH4AUDIOTIMEBEQUIET = 8.91f*TEMPO;

const char CH4AUDIODRAGITEMS[17] = "audio/chimes.wav";
const float CH4AUDIOTIMEDRAGITEMS = 6.01f*TEMPO;

    //These resources are for Chapter 5

const std::string CHIMESIMAGE = "res/blanks/blankBackground.png";

const std::string CHIME1IMAGE = "res/Chapter5/chime_1-2.png";
const std::string CHIME2IMAGE = "res/Chapter5/chime_2-2.png";
const std::string CHIME3IMAGE = "res/Chapter5/chime_3-2.png";
const std::string CHIME4IMAGE = "res/Chapter5/chime_4-2.png";
const std::string CHIME5IMAGE = "res/Chapter5/chime_5-2.png";
const std::string CHIME6IMAGE = "res/Chapter5/chime_6-2.png";
const std::string CHIMECENTERIMAGE = "res/Chapter5/chime_center.png";
const std::string CHIMEROPEIMAGE = "res/Chapter5/chime_rope-2.png";

const char CH5AUDIOLASTDAY[17] = "audio/chimes.wav";
const float CH5AUDIOTIMELASTDAY = 7.26f*TEMPO;

const char CH5AUDIODRAGROPE[17] = "audio/chimes.wav";
const float CH5AUDIOTIMEDRAGROPE = 3.16f*TEMPO;

const char CH5AUDIOHERETOHELP[17] = "audio/chimes.wav";
const float CH5AUDIOTIMEHERETOHELP = 8.72f*TEMPO;

const char CH5AUDIOCHIMES[17] = "audio/chimes.wav";
const float CH5AUDIOTIMECHIMES = 8.72f*TEMPO;


#endif // __RESOURCE_DEFINITIONS_H__
