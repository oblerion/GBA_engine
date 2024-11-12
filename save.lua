music_loaddir("asset")
music_playsound("laserShoot")
music_playmusic("Ghost_Zenith")
function collide(x,y,w,h,x2,y2,w2,h2)
    if x + w > x2 and
    y + h > y2 and
    x2 + w2 > x and
    y2 + h2 > h then
        return true
    end
    return false
end

function Player(px,py)
    local pl = {x=px,y=py,w=16*4,h=16*4}
    return pl
end

function Player_draw(player)
    rect(player.x,player.y,player.w,player.h,2)
end

function Bullet(px,py)
    local bul = {x=px,y=py,w=2,h=10}
    return bul
end

function Bullet_draw(bul)
    rect(bul.x,bul.y,bul.w,bul.h,19)
end

function BulletManager()
    local bulman={}
    return bulman
end

function BulletManager_add(bulman,px,py)
    local b = Bullet(px,py)
    table.insert(bulman,b)
end

function BulletManager_del(bulman,id)
    if id>0 and id<=#bulman then
        table.remove(bulman, id )
    end
end

function BulletManager_collide(bullman,px,py,pw,ph)
    for n,v in pairs(bullman) do 
        if collide(v.x,v.y,v.w,v.h,px,py,pw,ph)==true then
            return n
        end
    end
    return 0
end

function BulletManager_draw(bulman)
  for n,v in pairs(bulman) do 
    trace("id "..tostring(n).."x "..tostring(v.x).." y "..tostring(v.y))
    Bullet_draw(v)
  end
  --trace("-------------------")
end

local player = Player(23,423)
local bulman = BulletManager()
local timer_btn=0


function EGBA()
--    local x,y,btn1,btn3,btn2 = mouse()
--    player.x = x
--    player.y = y
    if btn(2) then
      player.x = player.x -3
    end
    if btn(3) then
      player.x = player.x +3
    end
    BulletManager_del(bulman,
      BulletManager_collide(bulman,player.x,player.y,player.w,player.h))
    -- player fire
    if timer_btn<=0 then
      if btn(0) then
        BulletManager_add(bulman,player.x+16,player.y-50)
        timer_btn=16
      end
    else
      timer_btn=timer_btn-1
    end
    -- move bullet and destroy
    for i=#bulman,1,-1 do
      if bulman[i].y < 0 then
        table.remove(bulman,i)
        music_stopmusic("Ghost_Zenith")
      else
        bulman[i].y = bulman[i].y-2
      end
    end

    Player_draw(player)
    BulletManager_draw(bulman)
end
