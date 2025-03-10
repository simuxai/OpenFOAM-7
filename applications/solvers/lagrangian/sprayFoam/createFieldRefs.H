const volScalarField& T = thermo.T();
const volScalarField& psi = thermo.psi();
const label inertIndex(composition.species()[inertSpecie]);
regionModels::surfaceFilmModel& surfaceFilm = tsurfaceFilm();

Switch solvePrimaryRegion
(
     pimple.dict().lookupOrDefault<Switch>("solvePrimaryRegion", true)
     );
