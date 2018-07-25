#pragma once

/// Mevcut oyun icin kullanacagimiz ekranlari ifade etmek icin kullanacagiz
/// Toplamda bes farkli ekran planliyoruz. Bunlarin her birini basit bir state machine
/// state leri olarak dusunebilirsiniz.
enum class GameScreenType
{
   eGAME_SCREEN_TYPE_SPLASH,
   eGAME_SCREEN_TYPE_MENU,
   eGAME_SCREEN_TYPE_GAME,
   eGAME_SCREEN_TYPE_HIGH_SCORES,
   eGAME_SCREEN_TYPE_OPTIONS,
   eGAME_SCREEN_TYPE_PAUSE,
   eGAME_SCREEN_TYPE_GAME_OVER,
};
