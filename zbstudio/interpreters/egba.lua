local win = ide.osname == "Windows"
local mac = ide.osname == "Macintosh"

return {
  name = "EGBA",
  description = "2d game egine, gba like",
  api = {"baselib","egba"},
  frun = function(self,wfilename,rundebug)
    local projdir = self:fworkdir(wfilename)
    if win==true then
      return CommandLineRun("egba.exe "..wfilename:GetFullPath(),projdir)
    elseif mac==true then
      return CommandLineRun("wine ".."egba.exe "..wfilename:GetFullPath(),projdir)
    else
      return CommandLineRun("./egba "..wfilename:GetFullPath(),projdir)
    end
  end
}
