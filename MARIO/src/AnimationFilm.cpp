#include "AnimationFilm.hpp"

byte AnimationFilm::GetTotalFrames (void) const
{
    return boxes.size();
}
Bitmap AnimationFilm::GetBitmap (void) const
{
    return bitmap;
}
const std::string AnimationFilm::GetId (void) const
{
    return id;
}
const Rect AnimationFilm::GetFrameBox (byte frameNo)  const
{
    assert(boxes.size() > frameNo);
    return boxes[frameNo];
}
void AnimationFilm::DisplayFrame (Bitmap dest,const Point& at, byte frameNo) const
{
    al_set_target_bitmap(dest);
    Rect rect = GetFrameBox(frameNo);
    al_draw_scaled_bitmap(bitmap, rect.GetX1(), rect.GetY1(), rect.GetX2()-rect.GetX1(),
                           rect.GetY2()-rect.GetY1(),at.GetX(), at.GetY(), 40, 40, 0);
    al_flip_display();
}
AnimationFilm::AnimationFilm (Bitmap _bitmap, const std::vector<Rect> _boxes, const std::string& _id)
    : bitmap(_bitmap), boxes(_boxes), id(_id) {}
