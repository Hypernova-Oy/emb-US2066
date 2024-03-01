package OLED::us2066::ROM_A;

use Modern::Perl;
binmode(STDOUT, ':utf8');
binmode(STDERR, ':utf8');
use utf8;

our $TRIANGLE_FILL_RIGHT  = chr(0x10);
our $TRIANGLE_FILL_LEFT   = chr(0x11);
our $TRIANGLE_UP_DOUBLE   = chr(0x12);
our $TRIANGLE_DOWN_DOUBLE = chr(0x13);
our $LESS_THAN_DOUBLE     = chr(0x14);
our $GREATER_THAN_DOUBLE  = chr(0x15);
our $ARROW_NW             = chr(0x16);
our $ARROW_NE             = chr(0x17);
our $ARROW_SW             = chr(0x18);
our $ARROW_SE             = chr(0x19);
our $CONE_UP              = chr(0x1A);
our $CONE_DOWN            = chr(0x1B);
our $ENTER_CHAR           = chr(0x1C);
our $WEDGE_UP             = chr(0x1D);
our $WEDGE_DOWN           = chr(0x1E);
our $BLOCK_FULL           = chr(0x1F);

our $SPACE                = chr(0x20);
our $EXCLAMATION_MARK     = chr(0x21);
our $DOUBLE_QUOTE         = chr(0x22);
our $NUMBER               = chr(0x23);
our $CURRENCY_SIGN        = chr(0x24); # ascii $
our $PERCENT              = chr(0x25);
our $AMPERSAND            = chr(0x26);
our $SINGLE_QUOTE         = chr(0x27);
our $PARENTHESIS_LEFT     = chr(0x28);
our $PARENTHESIS_RIGHT    = chr(0x29);
our $ASTERISK             = chr(0x2A);
our $PLUS                 = chr(0x2B);
our $COMMA                = chr(0x2C);
our $MINUS                = chr(0x2D);
our $PERIOD               = chr(0x2E);
our $SLASH                = chr(0x2F);

our $ZERO                 = chr(0x30);
our $ONE                  = chr(0x31);
our $TWO                  = chr(0x32);
our $THREE                = chr(0x33);
our $FOUR                 = chr(0x34);
our $FIVE                 = chr(0x35);
our $SIX                  = chr(0x36);
our $SEVEN                = chr(0x37);
our $EIGHT                = chr(0x38);
our $NINE                 = chr(0x39);
our $COLON                = chr(0x3A);
our $SEMICOLON            = chr(0x3B);
our $LESS_THAN            = chr(0x3C);
our $EQUALITY_SIGN        = chr(0x3D);
our $GREATER_THAN         = chr(0x3E);
our $QUESTION_MARK        = chr(0x3F);

our $EXCLAMATION_MARK_FLIPPED = chr(0x40); # ascii @
our $CAPITAL_A            = chr(0x41);
our $CAPITAL_B            = chr(0x42);
our $CAPITAL_C            = chr(0x43);
our $CAPITAL_D            = chr(0x44);
our $CAPITAL_E            = chr(0x45);
our $CAPITAL_F            = chr(0x46);
our $CAPITAL_G            = chr(0x47);
our $CAPITAL_H            = chr(0x48);
our $CAPITAL_I            = chr(0x49);
our $CAPITAL_J            = chr(0x4A);
our $CAPITAL_K            = chr(0x4B);
our $CAPITAL_L            = chr(0x4C);
our $CAPITAL_M            = chr(0x4D);
our $CAPITAL_N            = chr(0x4E);
our $CAPITAL_O            = chr(0x4F);
our $CAPITAL_P            = chr(0x50);
our $CAPITAL_Q            = chr(0x51);
our $CAPITAL_R            = chr(0x52);
our $CAPITAL_S            = chr(0x53);
our $CAPITAL_T            = chr(0x54);
our $CAPITAL_U            = chr(0x55);
our $CAPITAL_V            = chr(0x56);
our $CAPITAL_W            = chr(0x57);
our $CAPITAL_X            = chr(0x58);
our $CAPITAL_Y            = chr(0x59);
our $CAPITAL_Z            = chr(0x5A);
our $CAPITAL_A_UMLAUT     = chr(0x5B); # ascii [
our $CAPITAL_O_UMLAUT     = chr(0x5C); # ascii \
our $CAPITAL_N_TILDE      = chr(0x5D); # ascii ]
our $CAPITAL_U_UMLAUT     = chr(0x5E); # ascii ^
our $SECTION_SIGN         = chr(0x5F); # ascii _

our $QUESTION_MARK_FLIPPED = chr(0x60); # ascii `
our $SMALL_A              = chr(0x61);
our $SMALL_B              = chr(0x62);
our $SMALL_C              = chr(0x63);
our $SMALL_D              = chr(0x64);
our $SMALL_E              = chr(0x65);
our $SMALL_F              = chr(0x66);
our $SMALL_G              = chr(0x67);
our $SMALL_H              = chr(0x68);
our $SMALL_I              = chr(0x69);
our $SMALL_J              = chr(0x6A);
our $SMALL_K              = chr(0x6B);
our $SMALL_L              = chr(0x6C);
our $SMALL_M              = chr(0x6D);
our $SMALL_N              = chr(0x6E);
our $SMALL_O              = chr(0x6F);

our $SMALL_P              = chr(0x70);
our $SMALL_Q              = chr(0x71);
our $SMALL_R              = chr(0x72);
our $SMALL_S              = chr(0x73);
our $SMALL_T              = chr(0x74);
our $SMALL_U              = chr(0x75);
our $SMALL_V              = chr(0x76);
our $SMALL_W              = chr(0x77);
our $SMALL_X              = chr(0x78);
our $SMALL_Y              = chr(0x79);
our $SMALL_Z              = chr(0x7A);
our $SMALL_A_UMLAUT       = chr(0x7B); # ascii {
our $SMALL_O_UMLAUT       = chr(0x7C); # ascii |
our $SMALL_N_TILDE        = chr(0x7D); # ascii }
our $SMALL_U_UMLAUT       = chr(0x7E); # ascii ~
our $SMALL_A_GRAVE        = chr(0x7F); # ascii DEL

our $ZERO_SUPER           = chr(0x80);
our $ONE_SUPER            = chr(0x81);
our $TWO_SUPER            = chr(0x82);
our $THREE_SUPER          = chr(0x83);
our $FOUR_SUPER           = chr(0x84);
our $FIVE_SUPER           = chr(0x85);
our $SIX_SUPER            = chr(0x86);
our $SEVEN_SUPER          = chr(0x87);
our $EIGHT_SUPER          = chr(0x88);
our $NINE_SUPER           = chr(0x89);
our $HALF                 = chr(0x8A);
our $QUARTER              = chr(0x8B);
our $PLUS_MINUS           = chr(0x8C);
our $GREATER_OR_EQUAL     = chr(0x8D);
our $LESS_OR_EQUAL        = chr(0x8E);
our $MICRO_SIGN           = chr(0x8F);

our $MUSICAL_NOTE         = chr(0x90);
our $MUSICAL_NOTE_DOUBLE  = chr(0x91);
our $TURTLE               = chr(0x92); # no idea what this is
our $HEART                = chr(0x93);
our $DIAMOND              = chr(0x94);
our $TORCH                = chr(0x95);
our $CORNER_NW            = chr(0x96);
our $CORNER_SE            = chr(0x97);
our $QUOTE_BEGIN          = chr(0x98);
our $QUOTE_END            = chr(0x99);
our $LEFT_PARENTHESIS     = chr(0x9A);
our $RIGHT_PARENTHESIS    = chr(0x9B);
our $ALPHA                = chr(0x9C);
our $EPSILON              = chr(0x9D);
our $DELTA                = chr(0x9E);
our $EYE                  = chr(0x9F); # no idea what this is

our $AT_SIGN              = chr(0xA0);
our $POUND_SIGN           = chr(0xA1);
our $DOLLAR_SIGN          = chr(0xA2);
our $YEN_SIGN             = chr(0xA3);


our %translationMap = (
  'Ä' => $CAPITAL_A_UMLAUT,
  'Ö' => $CAPITAL_O_UMLAUT,
  'ä' => $SMALL_A_UMLAUT,
  'ö' => $SMALL_O_UMLAUT,
  '“' => $QUOTE_BEGIN,
  '”' => $QUOTE_END,
  '’' => $SINGLE_QUOTE,
  '—' => $MINUS,
  '@' => $AT_SIGN,
  '$' => $DOLLAR_SIGN,
);


=head translatePerlString

Perl strings need to be turned into ascii-strings and code points translated so we can support various characters from the display.

=cut

sub translatePerlString {
  require Encode;
  my ($perlString) = @_;
  #warn("Translating \$perlString='$perlString', utf='".(Encode::is_utf8($perlString) ? 'true' : 'false')."'");
  $perlString =~ s/([ÄÖäö“”’@\$—])/$translationMap{$1}/gsmu;

  if (1) {
    for (split(//, $perlString)) {
      warn("Wide character '$_' detected, ord='".ord($_)."'. Update the character encoding translation rules.") if (ord($_) >= 256);
    }
  }
  return $perlString;
}

1;
