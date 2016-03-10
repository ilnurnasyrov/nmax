require "mkmf"

extension_name = "bignums_elector"

$CFLAGS << ' -std=c99'

create_makefile(extension_name)
