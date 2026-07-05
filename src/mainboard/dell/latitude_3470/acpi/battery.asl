
/*
 * Minimal Dummy Battery Definition
 * Satisfies the build system without defining real hardware.
 */

DefinitionBlock (
    "battery.aml",  // Output Filename
    "SSDT",         // Table Signature
    0x02,           // Compliance Revision
    "DELL  ",       // OEM ID
    "LAT3470 ",      // Table ID
    0x00001000      // OEM Revision
)
{
    Scope (\_SB)
    {
        // Dummy Device to satisfy basic ACPI enumeration if needed
        Device (BAT0)
        {
            Name (_HID, EisaId ("PNP0C0A")) // Standard ACPI Battery Hardware ID
            Name (_UID, One)

            Method (_STA, 0, NotSerialized)
            {
                Return (0x00) // 0x00 means "Not Present" / Disabled
            }
        }
    }
}