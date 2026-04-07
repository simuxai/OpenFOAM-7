#include "fvCFD.H"

int main(int argc, char *argv[])
{
    #include "setRootCase.H"
    #include "createTime.H"
    #include "createMesh.H"

    Info<< "Reading field p\n" << endl;
    volScalarField p
    (
        IOobject
        (
            "p",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );

    // --- PARAMETERS ---
    scalar p_start = 1.0e6;
    scalar p_end   = 1.0e5;
    scalar y_start = -0.047;
    scalar y_end   = 0.0292;

    // --- APPLY GRADIENT ---
    forAll(mesh.C(), celli)
    {
        // Get the Y-coordinate of the cell center
        scalar y = mesh.C()[celli].y();

        // Only apply downstream of the throat
        if (y > y_start && y <= y_end)
        {
            scalar fraction = (y - y_start) / (y_end - y_start);
            p[celli] = p_start + (p_end - p_start) * fraction;
        }
    }

    Info<< "Writing field p with linear gradient..." << endl;
    p.write();

    Info<< "Done." << endl;
    return 0;
}
