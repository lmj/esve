
Dir.chdir("esve/engine") {
   [
      Dir["dim3/Frame*.{cxx,hxx}"],
      Dir["dim3/impl/Frame*.{cxx,hxx}"],
   ].flatten.each { |infile|
      outfile = infile.sub(%r!\Adim3!) { "dim4" }
      contents = File.open(infile) { |f| f.read }.gsub(%r!dim3!, "dim4")
      puts "#{infile} --> #{outfile}"
      File.open(outfile, "w") { |f| f.print contents }
   }
}
