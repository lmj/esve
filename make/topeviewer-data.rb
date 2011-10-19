

HEADER = <<EOS
<?xml version="1.0" encoding="us-ascii"?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head><title>topeviewer data</title>
<style type="text/css">
img { border: 0; padding: 0 2px; vertical-align: text-bottom; }
td  { font-family: monospace; padding: 2px 3px; text-align: right; vertical-align: bottom; white-space: pre; }
td:first-child { text-align: left; padding: 2px 10px 2px 3px; }
table { border: 0; }
a.symlink { font-style: italic; }
</style>
</head>
<body>
<h2>topeviewer data</h2>
<hr/>
<table>
EOS

def entry(filename)
   %Q{<tr><td><a href="#{filename}">#{filename}</a></td>}
end

FOOTER = <<EOS
</table>
<hr/>
</body>
</html>
EOS

Dir.chdir("documentation/topeviewer-data") {
   File.open("index.html", "w") { |file|
      file.puts HEADER
      Dir.glob("*.v").sort.each { |filename|
         file.puts entry(filename)
      }
      file.puts FOOTER
   }
}
