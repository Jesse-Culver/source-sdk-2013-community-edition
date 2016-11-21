$scale 20


$modelname		"Sphere.mdl"

$body sphere	"Sphere.dmx"

$staticprop
$surfaceprop	metal
$cdmaterials	"models"

$sequence idle	"Sphere.dmx"

$renamematerial "Sphere2" "Sphere"

$collisionmodel	"Sphere_Phys.dmx" { $concave }