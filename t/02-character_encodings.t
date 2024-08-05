use Test::More tests => 6;

use utf8;
binmode(STDOUT, ':utf8');
binmode(STDERR, ':utf8');
use Modern::Perl;

use OLED::us2066::ROM_A;

my %tests = (
  "Miehet tuhmat, naiset\$laiskat,\nTyttäret typerämielet.”" =>
  "Miehet tuhmat, naiset${OLED::us2066::ROM_A::DOLLAR_SIGN}laiskat,\nTytt{ret typer{mielet.${OLED::us2066::ROM_A::QUOTE_END}",

  'Öyllisess’ on pyytö@paikat,' =>
  "\\yllisess' on pyyt|${OLED::us2066::ROM_A::AT_SIGN}paikat,",

  '“Tuoli’ on kaunis kantamani, Ihana imettämäni.”' =>
  "${OLED::us2066::ROM_A::QUOTE_BEGIN}Tuoli' on kaunis kantamani, Ihana imett{m{ni.${OLED::us2066::ROM_A::QUOTE_END}",
);

foreach my $k (sort keys %tests) {
  my ($perlString, $oledString) = ($k, $tests{$k});
  is(OLED::us2066::ROM_A::translatePerlString($perlString), $oledString, "translatePerlString");
  is(OLED::us2066::ROM_A::translateOLEDString($oledString), $perlString, "translateOLEDString");
}
