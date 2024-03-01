use Test::More tests => 3;

use utf8;
binmode(STDOUT, ':utf8');
binmode(STDERR, ':utf8');
use Modern::Perl;

use OLED::us2066::ROM_A;

is(OLED::us2066::ROM_A::translatePerlString('“Tuoli’ on kaunis kantamani, Ihana imettämäni.”'), "${OLED::us2066::ROM_A::QUOTE_BEGIN}Tuoli' on kaunis kantamani, Ihana imett{m{ni.${OLED::us2066::ROM_A::QUOTE_END}");

is(OLED::us2066::ROM_A::translatePerlString("Miehet tuhmat, naiset\$laiskat,\nTyttäret typerämielet.”"), "Miehet tuhmat, naiset${OLED::us2066::ROM_A::DOLLAR_SIGN}laiskat,\nTytt{ret typer{mielet.${OLED::us2066::ROM_A::QUOTE_END}");

is(OLED::us2066::ROM_A::translatePerlString('Öyllisess’ on pyytö@paikat,'), "\\yllisess' on pyyt|${OLED::us2066::ROM_A::AT_SIGN}paikat,");
