#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Track Track;

struct Track
{
    char track_name[50];
    char composer_name[50];
    char track_media_type[5];
    char album[50];
    int track_duration_seconds;
    Track *next;
};

void print_tracks(Track *track, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("\nTrack %d:\n", i + 1);
        printf("Name: %s\n", track[i].track_name);
        printf("Composer: %s\n", track[i].composer_name);
        printf("Media Type: %s\n", track[i].track_media_type);
        printf("Album: %s\n", track[i].album);
        printf("Duration (seconds): %d\n", track[i].track_duration_seconds);
    }
}

void search_track(Track *track, int count)
{
    char search_input[15];
    printf("\ninput composer to search: ");
    scanf("%s", search_input);
    getchar();

    for (int i = 0; i < count; i++)
    {
        if (strcmp(track[i].composer_name, search_input) == 0)
        {
            printf("\nelement found at position: %d\n\n", i + 1);
            printf("name: %s\n", track[i].track_name);
            printf("composer: %s\n", track[i].composer_name);
            printf("media type: %s\n", track[i].track_media_type);
            printf("album: %s\n", track[i].album);
            printf("duration (seconds): %d\n", track[i].track_duration_seconds);
            break;
        }
    }
}

int compare(const void *a, const void *b)
{
    Track *trackA = (Track *)a;
    Track *trackB = (Track *)b;
    return (trackB->track_duration_seconds - trackA->track_duration_seconds);
}

Track *add_track_at_beginning(Track *track, int *count, Track new_track)
{
    *count += 1;
    track = realloc(track, (*count) * sizeof(Track));
    for (int i = *count - 1; i > 0; i--)
    {
        track[i] = track[i - 1];
    }
    track[0] = new_track;
    return track;
}

Track *add_track_at_end(Track *track, int *count, Track new_track)
{
    *count += 1;
    track = realloc(track, (*count) * sizeof(Track));
    track[*count - 1] = new_track;
    return track;
}

int main()
{
    int track_count = 10;
    Track *track = malloc(track_count * sizeof(Track));

    Track predefined_tracks[10] = {
        {"track1", "comp_1", "WAV", "album_1", 465, NULL},
        {"track2", "comp_2", "MP3", "album_2", 231, NULL},
        {"track3", "comp_1", "WAV", "album_2", 661, NULL},
        {"track4", "comp_3", "WAV", "album_3", 211, NULL},
        {"track5", "comp_2", "MP3", "album_2", 289, NULL},
        {"track6", "comp_2", "MP3", "album_3", 129, NULL},
        {"track7", "comp_1", "WAV", "album_3", 372, NULL},
        {"track8", "comp_1", "WAV", "album_2", 273, NULL},
        {"track9", "comp_3", "WAV", "album_1", 249, NULL},
        {"track10", "comp_2", "MP3", "album_2", 332, NULL}};

    for (int i = 0; i < track_count; i++)
    {
        track[i] = predefined_tracks[i];
    }

    int n;
    do
    {
        printf("\n////////////////////////////////////\n");
        printf("//  Menu:                         //\n");
        printf("//  1| Print tracks               //\n");
        printf("//  2| Search tracks              //\n");
        printf("//  3| Sort tracks by duration    //\n");
        printf("//  4| Add track at beginning     //\n");
        printf("//  5| Add track at end           //\n");
        printf("//  6| Exit                       //\n");
        printf("////////////////////////////////////\n");
        printf("\nYour selection:\n");
        scanf(" %d", &n);
        switch (n)
        {
        case 1:
            print_tracks(track, track_count);
            break;
        case 2:
            search_track(track, track_count);
            break;
        case 3:
            qsort(track, track_count, sizeof(Track), compare);

            printf("After sort:\n");
            for (int i = 0; i < track_count; i++)
            {
                printf("Name: %-14s\tDuration: %-5d seconds\n", track[i].track_name, track[i].track_duration_seconds);
            }
            break;
        case 4:
        {
            Track new_track;
            printf("Enter details of the track to add at the beginning:\n");
            printf("Name: ");
            scanf("%s", new_track.track_name);
            printf("Composer: ");
            scanf("%s", new_track.composer_name);
            printf("Media Type: ");
            scanf("%s", new_track.track_media_type);
            printf("Album: ");
            scanf("%s", new_track.album);
            printf("Duration (seconds): ");
            scanf("%d", &new_track.track_duration_seconds);

            track = add_track_at_beginning(track, &track_count, new_track);
            printf("Track added at the beginning successfully.\n");
            break;
        }
        case 5:
        {
            Track new_track;
            printf("Enter details of the track to add at the end:\n");
            printf("Name: ");
            scanf("%s", new_track.track_name);
            printf("Composer: ");
            scanf("%s", new_track.composer_name);
            printf("Media Type: ");
            scanf("%s", new_track.track_media_type);
            printf("Album: ");
            scanf("%s", new_track.album);
            printf("Duration (seconds): ");
            scanf("%d", &new_track.track_duration_seconds);

            track = add_track_at_end(track, &track_count, new_track);
            printf("Track added at the end successfully.\n");
            break;
        }

        case 6:
            printf("exit . . .");
            exit(1);
            break;
        default:
            printf("invalid option.");
            break;
        }
    } while (n != 6);

    free(track);

    return 0;
}
