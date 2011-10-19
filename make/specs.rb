
Dir.chdir("esve/geom") {
   Dir["dim3/specs/*.{cxx,hxx}"].each { |infile|
      contents = File.open(infile) { |f|
         f.read
      }.gsub(%r!dim3!) {
         "dim4"
      }.gsub(%r!pure!) {
         "quat"
      }

      outfile = infile.sub(%r!\Adim3!) { "dim4" }

      puts "#{infile} --> #{outfile}"
      File.open(outfile, "w") { |f| f.print contents }
   }
}

