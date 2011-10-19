
Dir.chdir("esve/viewers") {
   [
      "dim3/Simple_Viewer.hxx",
      "dim3/Simple_Viewer.cxx",
      "dim3/Surface_Viewer.hxx",
      "dim3/Surface_Viewer.template.cxx",
   ].flatten.each { |infile|
      outfile = infile.sub(%r!\Adim3!) { "dim4" }

      contents = File.open(infile) { |f|
         f.read
      }.gsub(%r!dim3!) {
         "dim4"
      }

      if infile =~ %r!/domains/!
         contents.gsub!(%r!pure!) { "quat" }
      end

      puts "#{infile} --> #{outfile}"
      File.open(outfile, "w") { |f| f.print contents }
   }
}

system("patch -p0 -R < make/viewers-modify.patch")
