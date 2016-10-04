use Modern::Perl;
use Module::Build;

my $build = Module::Build->new
    (
     module_name => 'OLED::us2066',
     dist_author => ['Olli-Antti Kivilahti <olli-antti.kivilahti@jns.fi>'],
     dist_abstract => 'Driver for the NHD OLEDs using the US2066 microcontroller',

     build_requires => {
	    'Modern::Perl' => '1',
     },

     requires => {
        
     }

    );

$build->create_build_script;
